# Vista Engine Architectural Blueprint

This document outlines the core architectural design for the Vista rendering engine. The primary goals are to support multiple graphics backends (e.g., OpenGL, Vulkan) and to provide a flexible, data-driven rendering pipeline.

## 1. Core Philosophy: Separation of Concerns

The fundamental principle is a strict separation between the "host application" (the `App` class, our sandbox) and the "rendering library" (the `IRenderer` and its associated components).

-   **The Host Application (`App`)**: Acts as the "scene director." It is responsible for *what* to draw. It manages scene logic, user input, and decides which objects to render in what order. It should have no knowledge of the specific graphics API being used.
-   **The Rendering Library (`IRenderer`)**: Acts as the "graphics driver." It is responsible for *how* to draw. It takes high-level commands from the host application and translates them into low-level, API-specific instructions for the GPU.

## 2. Multi-Backend Support: Interfaces and Factories

To support multiple graphics APIs, all GPU resources must be abstracted behind interfaces. The host application will only ever interact with these interfaces.

### Key Interfaces:
-   `IRenderer`: The main entry point for all rendering operations.
-   `IShader`: Represents a compiled shader program.
-   `IMesh`: Represents a geometric object with vertex and index buffers.
-   `ITexture`: (Future) Represents a texture resource.

### The Graphics Factory Pattern

The creation of concrete, API-specific objects (like `OpenGLShader` or `VulkanMesh`) is handled by a **Factory**. To maintain decoupling, the `IRenderer` itself will provide the correct factory.

```cpp
// Forward-declare the factory interface
class IGraphicsFactory;

class IRenderer {
public:
    // ...
    virtual IGraphicsFactory* getFactory() = 0;
};

// The factory interface defines how to create resources
class IGraphicsFactory {
public:
    virtual std::unique_ptr<IShader> createShader(const std::string& vertSrc, const std::string& fragSrc) = 0;
    virtual std::unique_ptr<IMesh> createMesh(const VertexData& vertices, const IndexData& indices) = 0;
    // ... other resource creation methods
};
```

This pattern ensures the host application can create all the resources it needs without ever including a backend-specific header like `OpenGLShader.h`.

**Example Workflow:**
```cpp
// 1. App creates a concrete renderer (the only place a concrete backend is named)
m_renderer = std::make_unique<OpenGLRenderer>(); 

// 2. App gets the corresponding factory from the renderer
IGraphicsFactory* factory = m_renderer->getFactory();

// 3. App uses the factory to create an API-agnostic shader resource
std::unique_ptr<IShader> myShader = factory->createShader(vertSource, fragSource);
```

## 3. The Flexible Rendering Pipeline: Data-Driven Render Passes

To give the user full control over the rendering process (e.g., 2D only, 3D only, or mixed), the pipeline is not hardcoded. Instead, it is defined by a list of **`RenderPass`** objects that the host application builds each frame.

### Data Structures:

```cpp
// A struct to define a single drawable object
struct Renderable {
    IMesh* mesh;
    IShader* shader;
    glm::mat4 transform; // The object's unique Model matrix
};

// A struct to define one complete pass of the renderer
struct RenderPass {
    Camera* camera; // The viewpoint for this pass
    std::vector<Renderable> renderables; // All objects to draw in this pass

    // Flags to control GPU state before the pass
    bool clearColorBuffer = true;
    bool clearDepthBuffer = true;
};
```

### Execution Flow:

The host application's main loop becomes very simple. It builds a `std::vector<RenderPass>` and hands it to the renderer.

```cpp
// In App::run()
m_renderer->beginFrame();

for (const auto& pass : m_render_passes) {
    m_renderer->executeRenderPass(pass);
}

m_renderer->endFrame();
```

The `IRenderer` is responsible for implementing `executeRenderPass`, which will iterate through the `Renderable` objects and issue the necessary draw calls.

## 4. Use Case Scenarios

This architecture allows the user of the library to easily configure the pipeline for different scenarios by modifying the `m_render_passes` vector.

### Scenario A: 2D Only

-   **Setup**: Create one `RenderPass`.
-   **Configuration**:
    -   `camera`: A `Camera` object with an orthographic projection (`glm::ortho`).
    -   `renderables`: A list of all 2D sprites, UI elements, etc.

### Scenario B: 3D Only

-   **Setup**: Create one `RenderPass`.
-   **Configuration**:
    -   `camera`: A `Camera` object with a perspective projection (`glm::perspective`).
    -   `renderables`: A list of all 3D models.

### Scenario C: 3D World with 2D UI

This is the most common game scenario, achieved by creating two `RenderPass` objects in a specific order.

-   **Setup**: Create a vector with two `RenderPass` objects.

-   **Pass 1: The 3D Scene**
    -   `camera`: The 3D perspective camera.
    -   `clearColorBuffer`: `true` (to clear the screen from the last frame).
    -   `clearDepthBuffer`: `true` (to ensure 3D objects occlude each other correctly).
    -   `renderables`: The list of all 3D models.

-   **Pass 2: The 2D UI**
    -   `camera`: The 2D orthographic camera.
    -   `clearColorBuffer`: `false` (IMPORTANT: We don't want to erase the 3D scene).
    -   `clearDepthBuffer`: `true` (IMPORTANT: This resets the depth buffer, ensuring all 2D UI elements draw on top of the 3D scene).
    -   `renderables`: The list of all 2D UI elements.

This design provides a robust, scalable, and backend-agnostic foundation for the Vista engine.
