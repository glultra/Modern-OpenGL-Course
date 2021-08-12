#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Reading Files
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
    
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
	
    void setVec2(const std::string& name, float x, float y);
    void setVec2(const std::string& name, const glm::vec2 &value);
	
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec3(const std::string& name, const glm::vec3 &value);
	
    void setVec4(const std::string& name, float x, float y, float z, float w);
    void setVec4(const std::string& name, const glm::vec4 &value);
	
    void setMat2(const std::string& name, const glm::mat2& value);
    void setMat3(const std::string& name, const glm::mat3& value);
    void setMat4(const std::string& name, const glm::mat4& value);
};