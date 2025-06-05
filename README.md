Vista is a custom general-purpose 2D/3D graphics engine designed for flexibility, performance, and ease of use. Built on C++ with a (yet-to-come) high-level Lua API, Vista aims to provide tools for creating visual experiences, whether in gaming or other graphical applications.

> Note: Vista is a personal, non-profit and educational project being developed by me alone, and is currently under heavy development. The engine is far from feature complete and ETA for new features may change over time.

## Features

- **Lightweight**: Good for fast rendering and efficient resource management.
- **Flexible API**: A high-level Lua interface allows for easier scripting and rapid iteration (TBD).
- **Mod-Friendly Architecture**: Designed to facilitate modding in games, ensuring ease of use for both developers and end-users.
- **Support for 2D and 3D Rendering**: Capable of rendering both 2D and 3D graphics.
- **Custom Shaders**: Create stunning visuals with the ability to implement custom shaders (TBD).

## Getting Started

### Prerequisites

- **C++17 or higher**: Ensure you have a compatible C++ compiler.
- **CMake**: Required for building the project.
- **OpenGL**: Make sure you have the OpenGL libraries installed.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/henryisaway/vista.git
   cd vista
   ```

2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Run CMake:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   make
   ```

5. Run the executable:
   ```bash
   ./Vista
   ```

## License

This project is licensed under the Apache License 2.0. See the LICENSE file for details.

## Contact

For inquiries or support, feel free to reach out:

    Email: henryisaway@gmail.com
    GitHub: henryisaway

## Roadmap
Please note that these are not hard deadlines. Features may be implemented ahead of time or after the ETA.
### Q2 2025: Codebase overhaul
- **Restructuring of the codebase**
  - Better implementation of the ECS architecture and organisation of the project.
- **Basic 2D Rendering**
  - Achieve basic 2D rendering capabilities; support for 2D images and built-in shapes.
- **Basic 3D Rendering**
  - Achieve basic 3D rendering capabilities; support for imported 3D models and built-in primitive models.
- **Basic Input Handling**
  - Support for interactions with keyboard and mouse input.
  
### Q3 2025: Core Engine Features
- **Asset Management System**
  - Develop a modular asset manager for handling textures, models, and sounds.
- **Custom Shaders**
  - Implement a system for end user to create and utilize custom shaders.
- **Lua API Integration**
  - Integration of the high-level Lua API for user scripting.

### Q4 2025: Advanced Features
- **Advanced 2D Rendering Support**
  - Add features for rendering advanced 2D graphics, including animated sprites and UI elements.
- **Advanced 3D Rendering Support**
  - Add features for rendering advanced 3D graphics, including animated 3D models.
- **Physics Simulation**
  - Implement basic physics interactions and collision detection.
 
### 2026 and Beyond
- **Advanced Features**
  - Introduce advanced rendering techniques (e.g., post-processing, lighting models).
- **Multi-threading Support**
  - Optimize performance with multi-threaded rendering and resource loading.
- **Vulkan backend**
  - Introduce a Vulkan backend implementation for Vista's rendering engine.