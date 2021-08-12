#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open The Files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		// Read The Files
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// Close The Files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Read as a string
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "FAILED::FILES::TO_READ\n";
		glfwTerminate();
		return;
	}

	// Read as a const char
	vertexShaderData = vertexCode.c_str();
	fragmentShaderData = fragmentCode.c_str();

	// vertex
	this->vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}
	//fragment
	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	//Program
	this->ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(this->ID);
}

void Shader::setBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}