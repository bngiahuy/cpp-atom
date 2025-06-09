#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

class Shader
{
public:
    unsigned int ID; // The OpenGL shader program ID

    // Constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath);

    // Use/activate the shader
    void use();

    // Utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const float *value) const; // For `glm::value_ptr(matrix)` or your `Mat4::data()`
    // void setMat4(const std::string &name, const Mat4& value) const; // If you have your own Mat4

private:
    // Utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, std::string type);
};