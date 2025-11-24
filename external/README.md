# External Dependencies

This folder contains third-party libraries required for the Graphics Programming Assignment.

## Required Libraries

All libraries must be downloaded and placed in their respective folders before building the project.

### Status Legend
- ❌ = Not downloaded yet
- ✅ = Downloaded and ready

### 1. GLFW - Window and Input Management
- **Folder**: `glfw/`
- **Status**: Check if `glfw/include/GLFW/glfw3.h` exists
- **Download**: https://www.glfw.org/download.html
- **See**: [glfw/README.md](glfw/README.md)

### 2. GLAD - OpenGL Function Loader
- **Folder**: `glad/`
- **Status**: Check if `glad/include/glad/glad.h` exists
- **Download**: https://glad.dav1d.de/
- **See**: [glad/README.md](glad/README.md)

### 3. GLM - OpenGL Mathematics
- **Folder**: `glm/`
- **Status**: Check if `glm/glm/glm.hpp` exists
- **Download**: https://github.com/g-truc/glm/releases
- **See**: [glm/README.md](glm/README.md)

## Quick Setup Guide

### Option 1: Manual Download (Recommended)

1. **Download GLFW**:
   - Visit https://www.glfw.org/download.html
   - Download Windows pre-compiled binaries (64-bit)
   - Extract and copy to `external/glfw/`

2. **Generate GLAD**:
   - Visit https://glad.dav1d.de/
   - Select: OpenGL 3.3+, Core profile
   - Generate and download
   - Extract and copy to `external/glad/`

3. **Download GLM**:
   - Visit https://github.com/g-truc/glm/releases
   - Download latest release
   - Extract and copy the inner glm folder to `external/glm/`

### Option 2: Using vcpkg (Alternative)

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

If using vcpkg, you'll need to update the project file to use vcpkg paths.

## Verification

After setting up all dependencies, your `external/` folder should look like:

```
external/
├── README.md (this file)
├── glfw/
│   ├── README.md
│   ├── include/
│   │   └── GLFW/
│   └── lib-vc2022/
│       └── glfw3.lib
├── glad/
│   ├── README.md
│   ├── include/
│   │   ├── glad/
│   │   └── KHR/
│   └── src/
│       └── glad.c
└── glm/
    ├── README.md
    └── glm/
        └── glm.hpp (and other files)
```

## Testing Your Setup

Run this checklist to verify:

```batch
# Check GLFW
dir external\glfw\include\GLFW\glfw3.h
dir external\glfw\lib-vc2022\glfw3.lib

# Check GLAD
dir external\glad\include\glad\glad.h
dir external\glad\src\glad.c

# Check GLM
dir external\glm\glm\glm.hpp
```

All commands should show files exist. If any fail, that library needs to be installed.

## Common Issues

### Issue: Files not found during build

**Symptoms**: Build errors about missing header files or libraries

**Solution**: 
1. Verify folder structure matches exactly as shown above
2. Check that you copied the correct folders (not just the downloaded zip)
3. Ensure GLFW lib folder matches your Visual Studio version

### Issue: "Cannot open file 'glfw3.lib'"

**Solution**: 
- Verify `lib-vc2022` folder exists (not just `lib`)
- For VS 2019, use `lib-vc2019`
- Check the .vcxproj file has correct library paths

### Issue: GLAD compilation errors

**Solution**: 
- Ensure `glad.c` is in the project and being compiled
- Verify both `glad.h` and `khrplatform.h` exist in include folders

## Why External Dependencies?

These libraries are not included in the repository because:
1. **License compliance** - each library has its own license
2. **Size** - libraries can be large and change frequently  
3. **Version control** - users may want different versions
4. **Platform differences** - different OS/compilers need different builds

## Alternative: Pre-built Setup

Some repositories provide a setup script or pre-built dependencies. If available, look for:
- `setup.bat` or `setup.sh` scripts
- `dependencies/` folder with pre-built libraries
- Release packages with dependencies included

## Next Steps

After setting up dependencies:
1. Return to the main [README.md](../README.md)
2. Follow the [Build Instructions](../docs/BUILD_INSTRUCTIONS.md)
3. Start developing!

## Need Help?

- Check individual README files in each subfolder
- See the detailed [Setup Dependencies Guide](../docs/SETUP_DEPENDENCIES.md)
- Verify your Visual Studio has C++ development tools installed
- Ensure Windows SDK is installed
