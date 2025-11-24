# External Dependencies Setup Guide

This document provides detailed instructions for setting up the external dependencies required for this OpenGL C++ project.

## Required Dependencies

### 1. GLFW (Graphics Library Framework)
GLFW is used for window creation, context management, and input handling.

**Download Steps:**
1. Visit https://www.glfw.org/download.html
2. Download the **Windows pre-compiled binaries**
3. Choose the 64-bit version
4. Extract the downloaded file
5. Copy the contents to create this structure:
   ```
   external/glfw/
   ├── include/
   │   └── GLFW/
   │       └── glfw3.h
   │       └── glfw3native.h
   └── lib-vc2022/
       └── glfw3.lib
   ```

**Version Recommendation:** 3.3.8 or later

### 2. GLAD (OpenGL Loader)
GLAD is used to load OpenGL function pointers.

**Download Steps:**
1. Go to https://glad.dav1d.de/
2. Configure the generator:
   - **Language**: C/C++
   - **Specification**: OpenGL
   - **API gl**: Version 3.3 (or higher)
   - **Profile**: Core
   - **Extensions**: Leave default or add specific ones if needed
   - Check "Generate a loader"
3. Click **Generate**
4. Download the zip file
5. Extract and organize files:
   ```
   external/glad/
   ├── include/
   │   ├── glad/
   │   │   └── glad.h
   │   └── KHR/
   │       └── khrplatform.h
   └── src/
       └── glad.c
   ```

**Important:** The glad.c file must be added to your project compilation!

### 3. GLM (OpenGL Mathematics)
GLM is a header-only C++ mathematics library for graphics.

**Download Steps:**
1. Visit https://github.com/g-truc/glm/releases
2. Download the latest release (0.9.9.8 or later)
3. Extract the archive
4. Copy the glm folder to create this structure:
   ```
   external/glm/
   └── glm/
       ├── glm.hpp
       ├── ext/
       ├── gtc/
       ├── gtx/
       └── ... (other GLM headers)
   ```

**Note:** GLM is header-only, no compilation needed!

## Directory Structure Verification

After setting up all dependencies, your `external/` folder should look like:

```
external/
├── glfw/
│   ├── include/
│   │   └── GLFW/
│   └── lib-vc2022/
│       └── glfw3.lib
├── glad/
│   ├── include/
│   │   ├── glad/
│   │   └── KHR/
│   └── src/
│       └── glad.c
└── glm/
    └── glm/
        └── (GLM headers)
```

## Alternative: Using vcpkg (Package Manager)

If you prefer using a package manager, you can use vcpkg:

```bash
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Install dependencies
.\vcpkg install glfw3:x64-windows
.\vcpkg install glad:x64-windows
.\vcpkg install glm:x64-windows

# Integrate with Visual Studio
.\vcpkg integrate install
```

Then modify the project file to use vcpkg paths instead of the `external/` folder.

## Troubleshooting

### Issue: "Cannot open include file: 'glad/glad.h'"
- Verify `external/glad/include/` exists and contains the glad headers
- Check the project's Additional Include Directories in project properties

### Issue: "Unresolved external symbol" errors
- Ensure `glad.c` is added to the project and being compiled
- Verify `glfw3.lib` exists in `external/glfw/lib-vc2022/`
- Check the project's Additional Library Directories

### Issue: "GLFW initialization failed"
- Make sure you're using the correct GLFW library version (64-bit for x64)
- Verify the lib-vc2022 folder matches your Visual Studio version

## OpenGL System Requirements

- **GPU**: Must support OpenGL 3.3 or higher
- **Drivers**: Update to the latest graphics drivers
- **OS**: Windows 10/11 recommended

To check your OpenGL version:
1. Run the application
2. Check the console output for "OpenGL Version"
3. Or use tools like GPU-Z or OpenGL Extensions Viewer

## Additional Resources

- GLFW Documentation: https://www.glfw.org/docs/latest/
- GLAD Documentation: https://github.com/Dav1dde/glad
- GLM Documentation: https://github.com/g-truc/glm
- OpenGL Reference: https://www.khronos.org/opengl/wiki/
