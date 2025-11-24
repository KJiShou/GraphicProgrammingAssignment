# Quick Start Guide

Get up and running with the Graphics Programming Assignment in 5 minutes!

## Prerequisites

Before you begin, ensure you have:
- ✅ **Windows 10 or 11**
- ✅ **Visual Studio 2022** (with C++ Desktop Development workload)
- ✅ **Git** (to clone the repository)

## Step 1: Clone the Repository (30 seconds)

```bash
git clone https://github.com/KJiShou/GraphicProgrammingAssignment.git
cd GraphicProgrammingAssignment
```

## Step 2: Download Dependencies (3 minutes)

You need three libraries. Quick links:

### GLFW
1. Download: https://www.glfw.org/download.html → **Windows pre-compiled binaries (64-bit)**
2. Extract zip file
3. Copy entire `include` folder to `external/glfw/include/`
4. Copy `lib-vc2022` folder to `external/glfw/lib-vc2022/`

### GLAD
1. Visit: https://glad.dav1d.de/
2. Set: Language=C/C++, API gl=3.3+, Profile=Core
3. Click **Generate** → Download zip
4. Extract and copy `include` folder to `external/glad/include/`
5. Extract and copy `src` folder to `external/glad/src/`

### GLM
1. Download: https://github.com/g-truc/glm/releases → latest release
2. Extract zip file
3. Find the **inner** `glm` folder (contains glm.hpp)
4. Copy it to `external/glm/glm/`

> 💡 **Tip**: See [external/README.md](external/README.md) for detailed instructions

## Step 3: Verify Setup (30 seconds)

Check that these files exist:
- `external/glfw/include/GLFW/glfw3.h`
- `external/glfw/lib-vc2022/glfw3.lib`
- `external/glad/include/glad/glad.h`
- `external/glad/src/glad.c`
- `external/glm/glm/glm.hpp`

## Step 4: Build and Run (1 minute)

1. **Open** `GraphicProgrammingAssignment.sln` in Visual Studio
2. **Select** Configuration: `Debug | x64`
3. **Press** `F7` to build (or Build → Build Solution)
4. **Press** `F5` to run (or Debug → Start Debugging)

You should see:
- ✅ A window titled "OpenGL Graphics Programming"
- ✅ A colored triangle (red, green, blue vertices)
- ✅ Console output showing OpenGL version

## What's Next?

### Explore the Code
- **src/main.cpp** - Main application and rendering loop
- **shaders/vertex.glsl** - Vertex shader
- **shaders/fragment.glsl** - Fragment shader

### Learn More
- [README.md](README.md) - Full project documentation
- [docs/BUILD_INSTRUCTIONS.md](docs/BUILD_INSTRUCTIONS.md) - Detailed build guide
- [docs/DIRECTX_INTEGRATION.md](docs/DIRECTX_INTEGRATION.md) - DirectX support

### Modify the Triangle

Try these simple modifications in `src/main.cpp`:

**Change triangle size:**
```cpp
// In vertices array, multiply positions by 1.5
-0.75f, -0.75f, 0.0f,  // Instead of -0.5f, -0.5f
```

**Change background color:**
```cpp
// In render loop
glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Dark grey instead of teal
```

**Add rotation:**
Add at top of main.cpp:
```cpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
```

Then modify the render loop to include transformations (requires updating shaders).

## Troubleshooting

### "Cannot open file 'glad/glad.h'"
→ Dependencies not set up correctly. Go back to Step 2.

### "LNK1104: cannot open file 'glfw3.lib'"
→ Check that `lib-vc2022` folder exists (not just `lib`).

### Black screen or crash on startup
→ Update graphics drivers. Verify GPU supports OpenGL 3.3+.

### Platform toolset error
→ Right-click project → Properties → General → Change Platform Toolset to match your VS version.

## Alternative: CMake Build

If you prefer CMake:

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug
```

## Controls

- **ESC** - Close the application
- **Alt+F4** - Close the window

## Project Structure

```
GraphicProgrammingAssignment/
├── src/              # Your C++ source files
├── include/          # Your header files  
├── shaders/          # GLSL shader files
├── external/         # Third-party libraries
└── docs/             # Documentation
```

## Tips for Success

1. **Start Simple**: Understand the triangle example before adding complexity
2. **Read the Shaders**: Understanding shaders is key to graphics programming
3. **Use Debugger**: Set breakpoints and inspect OpenGL state
4. **Check Console**: Application prints useful OpenGL information
5. **Commit Often**: Use git to track your changes

## Learning Resources

- **Learn OpenGL**: https://learnopengl.com/ (excellent tutorial series)
- **OpenGL Reference**: https://docs.gl/ (API documentation)
- **Graphics Programming**: https://www.scratchapixel.com/ (theory)

## Getting Help

1. Check documentation in `docs/` folder
2. Read error messages carefully
3. Verify all dependencies are correctly installed
4. Ensure your GPU supports OpenGL 3.3+

## Development Workflow

1. Make changes to code
2. Build (F7)
3. Run (F5)
4. Test your changes
5. Commit to git
6. Repeat!

---

**Ready to start?** Open `src/main.cpp` and begin experimenting! 🚀

**Questions?** Check the [full README](README.md) for comprehensive information.
