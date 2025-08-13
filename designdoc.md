# Jynx Design Document

## Overview

Jynx is a custom game engine focused on flexibility, ease of use, and performance, aimed at supporting both 2D and 3D rendering through a Lua API for end-user interaction. Jynx is structured around modular, high-level systems that allow easy updates, efficient management of entities and resources, and streamlined rendering.

Each core system has a distinct responsibility, creating a clear separation of concerns and making the engine modular and maintainable.
---
### 1. App Class
#### Purpose
Acts as the entry point and master orchestrator for Jynx. It handles engine initialization, loading settings, creating the main window, and starting the main loop.
#### Responsibilities
- Initialize the engine and all core systems.
- Handle the main loop, calling update and render functions.
- Manage lifecycle events (e.g., shutdown, restarting).
- Set up GLFW, GLAD, and the window for OpenGL.
#### Key Methods
- `App()`: Sets up core systems (ResourceManager, Scene, InputManager, etc.).
- `run()`: Main loop, which calls update and render methods on each tick.
- `~App()`: Releases resources and gracefully closes the engine.
---
### 2. RenderContext (Interface)
#### Purpose
Abstract interface that defines the generic rendering functions. Different implementations (e.g., OpenGLRenderContext) will implement this interface based on the API being used.
#### Responsibilities
- Define methods for rendering, such as `submitMesh()`, `drawMesh()`, and `setViewport()`.
- Provide API-agnostic commands for graphics operations, ensuring all specifics are encapsulated in the implementation.
#### Key Methods
- `initialize():` Sets up any required API-specific settings.
- `submitMesh(Mesh)`: Adds a mesh to the render queue.
- `drawMesh(Mesh)`: Renders a specific mesh.
- `setViewport(int width, int height)`: Resizes the viewport.
---
### 3. OpenGLRenderContext (API Implementation)
#### Purpose
Implements RenderContext specifically for OpenGL. Manages OpenGL resources like VAOs, VBOs, and EBOs, and handles all rendering-related OpenGL calls.
#### Responsibilities
- Implement API-specific rendering (e.g., loading shaders, managing buffers).
- Handle VAO, VBO, and EBO creation, binding, and deletion.
- Manage OpenGL settings, such as culling, depth testing, and shaders.
#### Key Methods
- `initialize()`: Loads shaders and configures OpenGL settings.
- `submitMesh(Mesh)`: Creates/binds VAOs and buffers specific to the mesh.
- `drawMesh(Mesh)`: Executes the OpenGL draw calls for the mesh.
- `updateBufferData()`: Updates vertex/element buffer data.
---
### 4. Renderer (or Render System)
#### Purpose
Manages the process of rendering entities within the Scene. Renderer acts as the high-level rendering interface and delegates low-level details to RenderContext.
#### Responsibilities
- Gather and organize renderable entities from Scene.
- Communicate with RenderContext to execute rendering of entities.
- Determine render order and manage frame-by-frame render data.
#### Key Methods
- `render(Scene)`: Collects entities with renderable components and submits them to RenderContext.
- `submit(Entity)`: Prepares an entity to be rendered by passing its data to RenderContext.
---
### 5. Scene / ECS
#### Purpose
Central storage for entities and components in the game world, providing an efficient way to query and organize them.
#### Responsibilities
- Maintain all entities and their components.
- Provide systems with easy access to entities that have specific component combinations.
- Manage creation, deletion, and updates of entities and their components.
#### Key Methods
- `addEntity(Entity)`: Creates a new entity and registers it in the scene.
- `getEntitiesWith(ComponentType)`: Queries entities that possess specific components.
---
### 6. Entity and Components
#### Entity
An ID representing an object in the game world. Holds a set of components that define its properties and behavior.
#### Component
A modular, single-purpose data structure that holds data (e.g., Transform, Mesh, Material). Components are added to entities to define their properties.
#### Standard Components
- Transform: Position, rotation, scale.
- Mesh: Geometry and buffer data for rendering.
- Material: Texture, shader data.
- Light: Lighting properties (for advanced rendering).
---
### 7. ResourceManager
#### Purpose
Manages and caches assets such as textures, shaders, and models. Responsible for loading and unloading resources.
#### Responsibilities
- Load resources on demand and cache them for reuse.
- Provide assets to systems that need them (e.g., Renderer).
- Release unused assets to save memory.
#### Key Methods
- `loadTexture(filePath)`: Loads a texture from a file and caches it.
- `getShader(name)`: Retrieves a cached shader.
- `releaseUnused()`: Frees memory from resources that are no longer in use.
---
### 8. InputManager
#### Purpose
Handles all user input, including keyboard, mouse, and controller events. Interfaces with GLFW for input polling.
#### Responsibilities
- Capture and process input events.
- Provide an API for querying input states.
- Communicate with entities or systems that require input.
#### Key Methods
- `isKeyPressed(key)`: Checks if a specific key is pressed.
- `getMousePosition()`: Retrieves the mouse position.
- `pollEvents()`: Updates the current state of all inputs.
---
### 9. Lua Scripting System
#### Purpose
Provides a high-level interface for gameplay scripting using Lua. Offers hooks for manipulating the Scene and interacting with components.
#### Responsibilities
- Load and run Lua scripts.
- Expose API functions for engine interaction (e.g., spawning entities, moving objects).
- Enable hot-reloading for faster iteration and testing.
#### Key Methods
- `loadScript(filePath)`: Loads and caches a Lua script.
- `executeFunction(funcName)`: Runs a specific Lua function.
- `registerAPI()`: Exposes engine functions and data to Lua.
---
## Data Flow Example
## Initialization:
- App sets up core systems (RenderContext, Scene, ResourceManager, etc.).
- RenderContext initializes OpenGL settings (OpenGLRenderContext).
## Main Loop (run by App):
- Update:
 - InputManager polls inputs.
 - Scene updates entity states and component data.
- Render:
 - Renderer queries Scene for renderable entities.
 - Renderer submits each entity’s data to RenderContext.
 - RenderContext makes API calls to render entities on screen.
## Resource Loading:
- Renderer or Scene requests assets (textures, shaders) from ResourceManager.
- ResourceManager loads, caches, and provides these assets as needed.
## 4. Scripting:
- Lua Scripting System allows users to define gameplay behaviors.
- Lua scripts interact with engine components via registered API functions.