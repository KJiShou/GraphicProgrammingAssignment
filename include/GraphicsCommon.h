#pragma once

// Common graphics programming utilities and constants

namespace Graphics {
    // Common constants
    const float PI = 3.14159265359f;
    const float TWO_PI = 6.28318530718f;
    const float HALF_PI = 1.57079632679f;
    
    // Window settings
    struct WindowConfig {
        unsigned int width = 800;
        unsigned int height = 600;
        const char* title = "Graphics Application";
        bool fullscreen = false;
        bool vsync = true;
    };
    
    // Color structure
    struct Color {
        float r, g, b, a;
        
        Color(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f)
            : r(red), g(green), b(blue), a(alpha) {}
        
        // Predefined colors
        static Color White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
        static Color Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
        static Color Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
        static Color Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
        static Color Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
        static Color Yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }
        static Color Cyan() { return Color(0.0f, 1.0f, 1.0f, 1.0f); }
        static Color Magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
    };
    
    // Vertex structure for 3D graphics
    struct Vertex {
        float x, y, z;        // Position
        float r, g, b;        // Color
        float nx, ny, nz;     // Normal (for lighting)
        float u, v;           // Texture coordinates
        
        Vertex(float px = 0.0f, float py = 0.0f, float pz = 0.0f)
            : x(px), y(py), z(pz),
              r(1.0f), g(1.0f), b(1.0f),
              nx(0.0f), ny(1.0f), nz(0.0f),
              u(0.0f), v(0.0f) {}
    };
    
    // Utility functions
    inline float DegreesToRadians(float degrees) {
        return degrees * (PI / 180.0f);
    }
    
    inline float RadiansToDegrees(float radians) {
        return radians * (180.0f / PI);
    }
}
