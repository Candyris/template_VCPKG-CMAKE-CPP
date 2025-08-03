# CMake & vcpkg Based C++ Project Templates

A collection of C++ project templates using vcpkg package manager and CMake build system for various graphics libraries and frameworks.

## Prerequisites

- **CMake** (version 3.15 or higher)
- **vcpkg** package manager installed on your system
- **Visual Studio** or compatible C++ compiler
- **Git** (for cloning repositories)

## Installation Steps

### 1. Setup vcpkg
1. Install vcpkg following the [official guide](https://vcpkg.io/en/getting-started.html)
2. Note the installation path (e.g., `C:/vcpkg/` or `C:/dev/vcpkg/`)
3. Integrate vcpkg with your development environment

### 2. Download Templates
1. Clone or download this repository
2. Extract to your desired workspace location

### 3. Choose Your Template
Navigate to the template directory you want to use:
- `OPENGL3/` - OpenGL 3.x with GLFW and GLAD
- `SDL2/` - SDL2 graphics library template  
- `RAYLIB/` - Raylib game development library

## Build Instructions

### Example: Building OpenGL3 Template

1. **Navigate to template directory:**
   ```bash
   cd OPENGL3
   ```

2. **Configure the project:**
   ```bash
   cmake --fresh -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/path_where_vcpkg_installed/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
   ```
   
   > **Note:** Replace `C:/path_where_vcpkg_installed/vcpkg` with your actual vcpkg installation path

3. **Build the project:**
   ```bash
   cmake --build build
   ```

### For Other Templates

The same build process applies to all templates. Just change the directory:

```bash
# For SDL2 template
cd SDL2
cmake --fresh -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/your_vcpkg_path/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build

# For Raylib template
cd RAYLIB
cmake --fresh -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/your_vcpkg_path/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build
```

## Template Features

### OpenGL3 Template
- **Libraries:** GLFW, GLAD, OpenGL 3.x
- **Use case:** Modern OpenGL applications, games, graphics programming
- **Dependencies:** Automatically managed via vcpkg

### SDL2 Template  
- **Libraries:** SDL2, SDL2_image, SDL2_mixer (example)
- **Use case:** Cross-platform games and multimedia applications
- **Dependencies:** Automatically managed via vcpkg

### Raylib Template
- **Libraries:** Raylib
- **Use case:** Simple game development, educational projects
- **Dependencies:** Automatically managed via vcpkg

## Configuration Notes

- **Triplet:** `x64-windows` is for 64-bit Windows. Use `x86-windows` for 32-bit
- **Fresh build:** The `--fresh` flag ensures a clean configuration
- **Toolchain:** The vcpkg toolchain file handles all dependency management

## Troubleshooting

### Common Issues

1. **vcpkg path not found:**
   - Verify your vcpkg installation path
   - Use forward slashes `/` or escaped backslashes `\\` in the path

2. **Missing dependencies:**
   - vcpkg will automatically install required packages on first build
   - This may take time depending on the template

3. **Build errors:**
   - Ensure your compiler supports C++17 or higher
   - Check that vcpkg integration is properly set up

## Quick Start

1. Install vcpkg and note its path
2. Clone this repository  
3. Choose a template directory (e.g., `OPENGL3`)
4. Run the three build commands with your vcpkg path
5. Find your executable in the `build/` directory

---

*Ready to start coding with modern C++ graphics libraries! 🚀*