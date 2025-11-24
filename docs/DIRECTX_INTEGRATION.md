# DirectX Integration Guide

This guide explains how to integrate DirectX alongside OpenGL in this project, or how to migrate to DirectX if desired.

## Overview

This project is currently set up with OpenGL 3.3+. DirectX is Microsoft's alternative graphics API, offering:
- Better integration with Windows
- Potentially better performance on Windows systems
- Access to DirectX-specific features
- Industry-standard for Windows game development

## DirectX vs OpenGL Comparison

| Feature | OpenGL | DirectX 11 | DirectX 12 |
|---------|--------|-----------|------------|
| Cross-Platform | ✅ Yes | ❌ Windows only | ❌ Windows only |
| Learning Curve | Medium | Medium | High |
| Performance | Good | Good | Excellent |
| Low-Level Control | Medium | Medium | High |
| Community Support | Large | Large | Growing |

## Prerequisites for DirectX Development

### Required Tools
1. **Windows 10/11** - DirectX 11/12 requires Windows 10 or later
2. **Visual Studio 2022** - Includes Windows SDK with DirectX
3. **Graphics Debugging Tools** - Available in Windows SDK

### No Additional Downloads Required
- DirectX SDK is included in Windows SDK (comes with Visual Studio)
- Headers and libraries are automatically available

## Integration Approach 1: Dual Rendering Backend

Create an abstraction layer that supports both OpenGL and DirectX.

### Step 1: Create Renderer Interface

Create `include/Renderer.h`:
```cpp
#pragma once

class Renderer {
public:
    virtual ~Renderer() = default;
    
    virtual bool Initialize(void* windowHandle, int width, int height) = 0;
    virtual void Shutdown() = 0;
    
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    
    virtual void Clear(float r, float g, float b, float a) = 0;
    virtual void DrawTriangle() = 0;
    
    virtual void* GetDevice() = 0;
};
```

### Step 2: Create OpenGL Implementation

Create `include/OpenGLRenderer.h` and `src/OpenGLRenderer.cpp` with current OpenGL code.

### Step 3: Create DirectX Implementation

Create `include/DirectXRenderer.h`:
```cpp
#pragma once
#include "Renderer.h"
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class DirectXRenderer : public Renderer {
public:
    bool Initialize(void* windowHandle, int width, int height) override;
    void Shutdown() override;
    
    void BeginFrame() override;
    void EndFrame() override;
    
    void Clear(float r, float g, float b, float a) override;
    void DrawTriangle() override;
    
    void* GetDevice() override { return m_device.Get(); }

private:
    ComPtr<ID3D11Device> m_device;
    ComPtr<ID3D11DeviceContext> m_context;
    ComPtr<IDXGISwapChain> m_swapChain;
    ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    
    ComPtr<ID3D11VertexShader> m_vertexShader;
    ComPtr<ID3D11PixelShader> m_pixelShader;
    ComPtr<ID3D11Buffer> m_vertexBuffer;
    ComPtr<ID3D11InputLayout> m_inputLayout;
    
    bool CreateDeviceAndSwapChain(void* windowHandle, int width, int height);
    bool CreateShaders();
    bool CreateVertexBuffer();
};
```

### Step 4: Update Project Configuration

Add to `.vcxproj` in ItemDefinitionGroup:
```xml
<Link>
    <AdditionalDependencies>
        opengl32.lib;glfw3.lib;
        d3d11.lib;dxgi.lib;d3dcompiler.lib;
        %(AdditionalDependencies)
    </AdditionalDependencies>
</Link>
```

## Integration Approach 2: DirectX Only

To migrate completely to DirectX:

### Step 1: Replace Window Management

Instead of GLFW, use native Win32 API or SDL2:
```cpp
// Win32 window creation
HWND hwnd = CreateWindowEx(
    0, className, L"DirectX Window",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    800, 600,
    NULL, NULL, hInstance, NULL
);
```

### Step 2: Initialize Direct3D 11

```cpp
// Create device and swap chain
DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
swapChainDesc.BufferCount = 1;
swapChainDesc.BufferDesc.Width = width;
swapChainDesc.BufferDesc.Height = height;
swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
swapChainDesc.OutputWindow = hwnd;
swapChainDesc.SampleDesc.Count = 1;
swapChainDesc.Windowed = TRUE;

D3D11CreateDeviceAndSwapChain(
    nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
    0, nullptr, 0, D3D11_SDK_VERSION,
    &swapChainDesc, &swapChain,
    &device, nullptr, &context
);
```

### Step 3: Create HLSL Shaders

Instead of GLSL, use HLSL for DirectX.

Create `shaders/vertex.hlsl`:
```hlsl
struct VS_INPUT {
    float3 position : POSITION;
    float3 color : COLOR;
};

struct VS_OUTPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    output.color = input.color;
    return output;
}
```

Create `shaders/pixel.hlsl`:
```hlsl
struct PS_INPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

float4 main(PS_INPUT input) : SV_TARGET {
    return float4(input.color, 1.0f);
}
```

### Step 4: Compile Shaders

```cpp
D3DCompileFromFile(
    L"shaders/vertex.hlsl",
    nullptr, nullptr, "main", "vs_5_0",
    0, 0, &vertexShaderBlob, nullptr
);

device->CreateVertexShader(
    vertexShaderBlob->GetBufferPointer(),
    vertexShaderBlob->GetBufferSize(),
    nullptr, &vertexShader
);
```

## Recommended Learning Path

1. **Week 1-2**: Master current OpenGL implementation
2. **Week 3**: Study DirectX 11 basics
3. **Week 4**: Implement simple DirectX triangle
4. **Week 5+**: Add features to both renderers or choose one

## Resources

### DirectX Documentation
- [DirectX 11 Programming Guide](https://docs.microsoft.com/en-us/windows/win32/direct3d11/dx-graphics-overviews)
- [DirectX 12 Programming Guide](https://docs.microsoft.com/en-us/windows/win32/direct3d12/directx-12-programming-guide)

### Tutorials
- [RasterTek DirectX 11 Tutorials](http://www.rastertek.com/tutdx11.html)
- [Braynzar Soft DirectX Tutorials](https://www.braynzarsoft.net/viewtutorial/q16390-braynzar-soft-directx-11-tutorials)
- [Microsoft DirectX Samples](https://github.com/microsoft/DirectX-Graphics-Samples)

### Books
- "Introduction to 3D Game Programming with DirectX 11" by Frank D. Luna
- "Practical Rendering and Computation with Direct3D 11" by Jason Zink

## Next Steps

1. Complete the OpenGL implementation first
2. Study DirectX fundamentals
3. Decide on integration approach
4. Implement DirectX backend
5. Compare performance and features

## Notes

- DirectX 12 offers more control but is significantly more complex
- DirectX 11 is more similar to OpenGL in abstraction level
- Consider your project requirements and timeline
- OpenGL knowledge transfers well to DirectX concepts
