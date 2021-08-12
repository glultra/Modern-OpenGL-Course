#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Reading Files
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
private:
    std::string vertexCode, fragmentCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;
    std::stringstream vertexShaderStream, fragmentShaderStream;
    const char* vertexShaderData, * fragmentShaderData;
    unsigned int vertex, fragment;
public:
    unsigned int ID;

    // Constructor
    Shader(const char* vertexPath, const char* fragmentPath);

    // use
    void use();
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
};