#pragma once

#include <string>

// Shader utility class for loading and managing shaders
// NOTE: This is a template/placeholder for future development
// The current implementation in main.cpp uses basic shader loading functions
// This class can be implemented later to provide a cleaner shader management interface

namespace Graphics {

class Shader {
public:
    unsigned int ID;  // Shader program ID

    // Constructor (optional - can load and compile immediately)
    Shader() : ID(0) {}
    
    // Load shader from file paths
    Shader(const char* vertexPath, const char* fragmentPath);
    
    // Use/activate the shader
    void Use() const;
    
    // Utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat4(const std::string& name, const float* value) const;
    
    // Delete shader program
    void Delete();

private:
    // Helper function to check compilation/linking errors
    void CheckCompileErrors(unsigned int shader, const std::string& type);
};

// Example implementation notes:
// 
// 1. Constructor implementation would:
//    - Load shader source from files
//    - Compile vertex and fragment shaders
//    - Link them into a program
//    - Store the program ID
//
// 2. Use() would call glUseProgram(ID)
//
// 3. SetXXX functions would use glGetUniformLocation and glUniformXXX
//
// 4. This allows cleaner code like:
//    Shader myShader("vertex.glsl", "fragment.glsl");
//    myShader.Use();
//    myShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
//
// See main.cpp for current shader loading implementation
// You can refactor that code into this class for better organization

} // namespace Graphics
