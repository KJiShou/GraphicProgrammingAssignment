# GraphicProgrammingAssignment
Degree-Y2S2 Graphics Programming Project

## Project Overview
This is an OpenGL C++ graphics programming project designed to be developed using Microsoft Visual Studio. The project includes support for modern OpenGL rendering with potential for DirectX integration.

## Prerequisites
- **Microsoft Visual Studio 2022** (or later) with C++ development tools
- **Windows 10/11** (for DirectX support)
- **Git** for version control

## Project Structure
```
GraphicProgrammingAssignment/
├── src/                    # Source files (.cpp)
├── include/                # Header files (.h)
├── shaders/                # GLSL shader files
├── lib/                    # Library files
├── external/               # External dependencies (GLFW, GLAD, GLM)
├── docs/                   # Documentation
├── bin/                    # Compiled binaries (generated)
└── obj/                    # Intermediate object files (generated)
```

## Setup Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/KJiShou/GraphicProgrammingAssignment.git
cd GraphicProgrammingAssignment
```

### 2. Download Dependencies
You need to download and set up the following libraries:

#### GLFW (Window and Input Management)
1. Download GLFW from: https://www.glfw.org/download.html
2. Extract to `external/glfw/`
3. Ensure the structure is: `external/glfw/include/` and `external/glfw/lib-vc2022/`

#### GLAD (OpenGL Function Loader)
1. Go to: https://glad.dav1d.de/
2. Configure:
   - Language: C/C++
   - Specification: OpenGL
   - API gl: Version 3.3+
   - Profile: Core
3. Generate and download
4. Extract to `external/glad/` with structure:
   - `external/glad/include/`
   - `external/glad/src/glad.c`

#### GLM (OpenGL Mathematics)
1. Download from: https://github.com/g-truc/glm/releases
2. Extract to `external/glm/`
3. Ensure headers are in `external/glm/glm/`

### 3. Build the Project

#### Using Visual Studio GUI
1. Open `GraphicProgrammingAssignment.sln` in Visual Studio
2. Select build configuration (Debug or Release)
3. Build > Build Solution (or press F7)
4. Run > Start Debugging (or press F5)

#### Using MSBuild (Command Line)
```bash
# Open Developer Command Prompt for Visual Studio
msbuild GraphicProgrammingAssignment.sln /p:Configuration=Debug /p:Platform=x64
```

### 4. Running the Application
- After building, the executable will be in `bin/Debug-x64/` or `bin/Release-x64/`
- Run `GraphicProgrammingAssignment.exe`
- You should see a window with a colored triangle rendered using OpenGL

## Features
- ✅ OpenGL 3.3+ Core Profile
- ✅ GLFW for window management
- ✅ GLAD for OpenGL function loading
- ✅ Basic shader support (vertex and fragment shaders)
- ✅ Colored triangle rendering example
- ✅ Visual Studio 2022 project files
- ⏳ DirectX integration (future enhancement)

## DirectX Integration (Future)
To integrate DirectX alongside OpenGL:

1. **Add DirectX SDK**:
   - Modern Windows 10/11 SDK includes DirectX
   - Already available in Visual Studio installation

2. **Modify Project Settings**:
   - Add DirectX include directories
   - Link DirectX libraries (d3d11.lib, dxgi.lib, d3dcompiler.lib)

3. **Implementation Approach**:
   - Create separate rendering backends (OpenGL and DirectX)
   - Use renderer abstraction pattern
   - Allow switching between renderers at runtime or compile-time

## Controls
- **ESC**: Close the application

## Troubleshooting

### Missing Dependencies
- Ensure all external libraries are properly downloaded and placed in `external/` folder
- Check that library paths match in the .vcxproj file

### Build Errors
- Verify Visual Studio 2022 (v143 toolset) is installed
- Check Windows SDK version is compatible
- Ensure C++17 standard is supported

### OpenGL Initialization Fails
- Update your graphics drivers
- Verify OpenGL 3.3+ support on your GPU

## Development Roadmap
- [x] Basic OpenGL setup
- [x] Shader loading system
- [x] Triangle rendering
- [ ] 3D transformations with GLM
- [ ] Texture loading and mapping
- [ ] Camera system
- [ ] Lighting (Phong/Blinn-Phong)
- [ ] Model loading (OBJ/FBX)
- [ ] DirectX 11/12 backend
- [ ] Advanced rendering techniques

## Resources
- [Learn OpenGL](https://learnopengl.com/) - Comprehensive OpenGL tutorial
- [OpenGL Documentation](https://www.khronos.org/opengl/)
- [GLFW Documentation](https://www.glfw.org/documentation.html)
- [DirectX Documentation](https://docs.microsoft.com/en-us/windows/win32/directx)

## License
See LICENSE file for details.

## Author
KJiShou - Year 2 Semester 2 Graphics Programming Assignment
