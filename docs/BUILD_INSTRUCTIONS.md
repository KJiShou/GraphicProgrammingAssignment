# Build Instructions

This document provides detailed instructions for building the Graphics Programming Assignment project.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Building with Visual Studio (Recommended)](#building-with-visual-studio)
3. [Building with CMake](#building-with-cmake)
4. [Building from Command Line](#building-from-command-line)
5. [Troubleshooting](#troubleshooting)

## Prerequisites

Before building, ensure you have:
- ✅ Cloned the repository
- ✅ Downloaded all external dependencies (see [SETUP_DEPENDENCIES.md](SETUP_DEPENDENCIES.md))
- ✅ Visual Studio 2022 installed with C++ development tools
- ✅ Windows 10 or later

## Building with Visual Studio

This is the **recommended** method for Windows development.

### Step-by-Step Guide

1. **Open the Solution**
   - Navigate to the project directory
   - Double-click `GraphicProgrammingAssignment.sln`
   - Visual Studio will open the project

2. **Select Build Configuration**
   - At the top toolbar, you'll see configuration dropdowns
   - Select either:
     - `Debug | x64` - for development and debugging
     - `Release | x64` - for optimized builds

3. **Build the Project**
   - Method 1: Press `F7` or `Ctrl+Shift+B`
   - Method 2: Menu > Build > Build Solution
   - Method 3: Right-click on project > Build

4. **Run the Application**
   - Press `F5` to run with debugging
   - Press `Ctrl+F5` to run without debugging
   - Or click the green play button (▶) in the toolbar

### Expected Output

After building successfully:
- Executable location: `bin/Debug-x64/GraphicProgrammingAssignment.exe` or `bin/Release-x64/GraphicProgrammingAssignment.exe`
- Build logs will appear in the Output window
- A window should open displaying a colored triangle

## Building with CMake

CMake provides a cross-platform build system alternative.

### Windows with Visual Studio

```bash
# Create build directory
mkdir build
cd build

# Generate Visual Studio solution
cmake .. -G "Visual Studio 17 2022" -A x64

# Build the project
cmake --build . --config Debug

# Or open the generated solution in Visual Studio
start GraphicProgrammingAssignment.sln
```

### With DirectX Support

```bash
cmake .. -G "Visual Studio 17 2022" -A x64 -DUSE_DIRECTX=ON
cmake --build . --config Debug
```

## Building from Command Line

### Using MSBuild (Developer Command Prompt)

1. Open **Developer Command Prompt for VS 2022**

2. Navigate to project directory:
   ```cmd
   cd path\to\GraphicProgrammingAssignment
   ```

3. Build the solution:
   ```cmd
   # Debug build
   msbuild GraphicProgrammingAssignment.sln /p:Configuration=Debug /p:Platform=x64

   # Release build
   msbuild GraphicProgrammingAssignment.sln /p:Configuration=Release /p:Platform=x64
   ```

4. Run the executable:
   ```cmd
   bin\Debug-x64\GraphicProgrammingAssignment.exe
   ```

### Advanced MSBuild Options

```cmd
# Clean build
msbuild GraphicProgrammingAssignment.sln /t:Clean /p:Configuration=Debug /p:Platform=x64

# Rebuild (clean + build)
msbuild GraphicProgrammingAssignment.sln /t:Rebuild /p:Configuration=Debug /p:Platform=x64

# Verbose output
msbuild GraphicProgrammingAssignment.sln /v:detailed /p:Configuration=Debug /p:Platform=x64
```

## Build Configurations

### Debug Configuration
- **Purpose**: Development and debugging
- **Optimizations**: Disabled
- **Debug Info**: Full
- **Preprocessor**: `_DEBUG`
- **Runtime Library**: Multi-threaded Debug DLL
- **Output**: `bin/Debug-x64/`

### Release Configuration
- **Purpose**: Final deployment
- **Optimizations**: Enabled (speed)
- **Debug Info**: Minimal
- **Preprocessor**: `NDEBUG`
- **Runtime Library**: Multi-threaded DLL
- **Output**: `bin/Release-x64/`

## Verifying the Build

After building, verify everything works:

1. **Check executable exists**:
   ```cmd
   dir bin\Debug-x64\GraphicProgrammingAssignment.exe
   ```

2. **Run the application**:
   ```cmd
   cd bin\Debug-x64
   GraphicProgrammingAssignment.exe
   ```

3. **Expected behavior**:
   - Window opens with title "OpenGL Graphics Programming"
   - Console shows OpenGL version info
   - Triangle is rendered with RGB colors
   - Press ESC to close

## Troubleshooting

### Error: "Cannot open include file: 'glad/glad.h'"

**Solution**:
- Ensure `external/glad/include/` exists
- Check project properties > C/C++ > Additional Include Directories

### Error: "LNK1104: cannot open file 'glfw3.lib'"

**Solution**:
- Verify `external/glfw/lib-vc2022/glfw3.lib` exists
- Check project properties > Linker > Additional Library Directories

### Error: "Unresolved external symbol" for glad functions

**Solution**:
- Ensure `external/glad/src/glad.c` is included in the project
- Verify it's being compiled (check Solution Explorer)

### Error: Platform toolset not found

**Solution**:
- Install Visual Studio 2022 C++ build tools
- Or modify project to use your installed toolset:
  - Right-click project > Properties
  - Configuration Properties > General
  - Change Platform Toolset to your version (e.g., v142 for VS 2019)

### Application crashes on start

**Solution**:
1. Check OpenGL driver support:
   - Update graphics drivers
   - Verify GPU supports OpenGL 3.3+

2. Verify dependencies are in correct locations

3. Run in Debug mode and check Output window for errors

### Window opens but shows black screen

**Solution**:
- Verify shader files exist in `shaders/` directory
- Check console output for shader compilation errors
- Ensure working directory is set to project root

## Performance Notes

### Debug vs Release
- **Debug**: 10-50% slower, enables validation layers
- **Release**: Full optimization, recommended for performance testing

### Recommended Testing Approach
1. Develop in Debug mode
2. Test functionality in Debug mode
3. Test performance in Release mode
4. Deploy Release build

## Next Steps

After successful build:
1. Read the main [README.md](../README.md) for project overview
2. Explore the [DirectX Integration Guide](DIRECTX_INTEGRATION.md)
3. Start developing your graphics features!

## Additional Resources

- [Visual Studio Build Documentation](https://docs.microsoft.com/en-us/cpp/build/)
- [MSBuild Reference](https://docs.microsoft.com/en-us/visualstudio/msbuild/)
- [CMake Documentation](https://cmake.org/documentation/)
