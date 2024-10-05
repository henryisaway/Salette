# Jynx

Jynx is my custom 2D and 3D graphics engine written in C++ and built with OpenGL. It is both a learning project and foundation for any future projects that require graphics, such as simulations, game development, and more. It aims to be a flexible, performant graphics engine that allows for easy modding of any programs that use it.

> **Note:** Jynx is currently under heavy development. At the moment, it can only render textured 3D cubes. 3D model handling and 2D features are not yet implemented, and the engine is far from feature-complete.

## Features

- **Basic 3D Rendering**: Currently capable of rendering textured 3D cubes.
- **OpenGL Powered**: Efficient cross-platform rendering using OpenGL.
- **Entity-Component-System (ECS)**: Modular and scalable approach to managing game objects.
- **Mod-Friendly Design**: Future-proofed for games with modding support.

## Getting Started

### Prerequisites

- C++17 or higher
- OpenGL 3.3 or higher
- CMake 3.10 or higher (for building the project)
- A compatible compiler (e.g., GCC or MSVC)

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/henryisaway/jynx.git
   cd jynx
   ```

2. Create a build directory and configure the project with CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. Build the project:
   ```bash
   make
   ```

4. Run the executable:
   ```bash
   ./Jynx
   ```

## Roadmap
*in order of priority*
1. Restructuring of the codebase for better scalability
2. Add 2D graphics support.
3. Implement 3D model handling.
4. Integrate Lua scripting for hot reloading and faster iteration speeds.
5. Implement multi-threading for ECS architecture.
6. Add physics engine support.
7. Enhance tools for asset importing.

## Contributing

If you’d like to contribute, feel free to fork the repository and submit a pull request, or open an issue to discuss any changes or improvements.
