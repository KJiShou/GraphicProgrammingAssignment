# Contributing to Graphics Programming Assignment

Thank you for your interest in contributing to this project! This document provides guidelines and best practices for contributing.

## Getting Started

1. **Fork** the repository
2. **Clone** your fork locally
3. **Set up** the development environment (see [QUICKSTART.md](docs/QUICKSTART.md))
4. **Create** a new branch for your feature or fix

## Development Workflow

### 1. Create a Branch

```bash
git checkout -b feature/your-feature-name
# or
git checkout -b fix/your-bug-fix
```

Branch naming conventions:
- `feature/` - New features
- `fix/` - Bug fixes
- `docs/` - Documentation changes
- `refactor/` - Code refactoring
- `test/` - Adding or updating tests

### 2. Make Your Changes

Follow the coding standards outlined below.

### 3. Test Your Changes

- Build the project in both Debug and Release configurations
- Test your changes thoroughly
- Ensure existing functionality still works

### 4. Commit Your Changes

Write clear, descriptive commit messages:

```bash
git commit -m "Add: Camera rotation with mouse input"
git commit -m "Fix: Memory leak in texture loading"
git commit -m "Docs: Update shader documentation"
```

Commit message format:
- Start with a verb (Add, Fix, Update, Refactor, etc.)
- Be concise but descriptive
- Reference issues if applicable: `Fix #123: Resolve crash on startup`

### 5. Push and Create Pull Request

```bash
git push origin feature/your-feature-name
```

Then create a pull request on GitHub.

## Coding Standards

### C++ Style Guidelines

1. **Naming Conventions**:
   - Classes: `PascalCase` (e.g., `Shader`, `Camera`)
   - Functions: `PascalCase` (e.g., `LoadTexture()`, `UpdateCamera()`)
   - Variables: `camelCase` (e.g., `vertexBuffer`, `shaderProgram`)
   - Constants: `UPPER_CASE` (e.g., `MAX_LIGHTS`, `PI`)
   - Private members: prefix with `m_` (e.g., `m_vertexArray`)

2. **Formatting**:
   - Use 4 spaces for indentation (no tabs)
   - Opening braces on new line (Allman style)
   - Line length: max 100 characters
   - Use `.clang-format` configuration provided

3. **Comments**:
   - Use `//` for single-line comments
   - Use `/* */` for multi-line comments
   - Document all public API functions
   - Explain complex algorithms

Example:
```cpp
class Shader
{
public:
    // Load and compile shader from files
    Shader(const char* vertexPath, const char* fragmentPath);
    
    // Activate the shader program
    void Use() const;
    
private:
    unsigned int m_programID;
};
```

### GLSL Shader Style

1. **Naming**:
   - Inputs: prefix with `a` for attributes (e.g., `aPosition`)
   - Outputs: prefix with `v` for varying (e.g., `vTexCoord`)
   - Uniforms: descriptive names (e.g., `modelMatrix`)

2. **Formatting**:
   - 4 spaces for indentation
   - Consistent bracket style

Example:
```glsl
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPosition, 1.0);
    vTexCoord = aTexCoord;
}
```

### File Organization

- **Header files** (`.h`): Place in `include/`
- **Source files** (`.cpp`): Place in `src/`
- **Shader files** (`.glsl`): Place in `shaders/`
- **Documentation** (`.md`): Place in `docs/`

## What to Contribute

### Good First Issues

- Fix typos in documentation
- Add code comments
- Improve error messages
- Add input validation
- Create example programs

### Feature Ideas

- Camera system (FPS, orbital)
- Lighting (Phong, PBR)
- Texture loading
- Model loading (OBJ, FBX)
- Post-processing effects
- ImGui integration
- DirectX backend
- Shadow mapping
- Normal mapping

### Bug Fixes

- Check the Issues tab for reported bugs
- Test edge cases
- Improve error handling

## Testing Guidelines

### Manual Testing

1. Build in Debug mode
2. Build in Release mode
3. Test on different graphics cards (if possible)
4. Verify no memory leaks (use Visual Studio Diagnostic Tools)
5. Check console output for errors

### Performance Testing

- Use Release build for performance testing
- Profile with Visual Studio Performance Profiler
- Monitor frame times
- Check GPU usage

## Documentation

When adding features, update relevant documentation:

- Update README.md if adding major features
- Add to QUICKSTART.md if it affects setup
- Create new docs in `docs/` for complex features
- Add code comments for API documentation

## Pull Request Guidelines

### Before Submitting

- [ ] Code builds without errors
- [ ] Code builds without warnings (or document why warnings are acceptable)
- [ ] Changes have been tested
- [ ] Documentation is updated
- [ ] Commit messages are clear
- [ ] Code follows style guidelines

### PR Description

Include in your PR description:
- What changes were made
- Why the changes were necessary
- How to test the changes
- Screenshots/videos for visual changes
- Any breaking changes

Example:
```markdown
## Changes
- Added camera rotation with mouse input
- Added WASD movement controls

## Why
- Requested feature for better scene navigation

## Testing
1. Build and run the application
2. Click and drag mouse to rotate camera
3. Use WASD keys to move

## Screenshots
[Include screenshot if applicable]
```

## DirectX Contributions

If contributing DirectX code:

1. Maintain compatibility with OpenGL version
2. Use abstraction layer (see `docs/DIRECTX_INTEGRATION.md`)
3. Document DirectX-specific requirements
4. Test on Windows 10/11

## Code Review Process

1. Maintainers will review your PR
2. Address any feedback or requested changes
3. Once approved, your PR will be merged
4. Your contribution will be credited!

## Questions?

- Open an issue for questions
- Check existing documentation
- Review closed issues and PRs for similar topics

## License

By contributing, you agree that your contributions will be licensed under the same license as the project (see LICENSE file).

## Acknowledgments

Contributors will be acknowledged in the project documentation. Thank you for helping improve this project!

---

**Happy Coding!** 🎮✨
