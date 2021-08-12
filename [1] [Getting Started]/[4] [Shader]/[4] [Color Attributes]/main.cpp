#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float vertices[] =
{
	/* Position */		/* Color */
	-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f,0.0f,	0.0f,0.0f,1.0f,
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"	ourColor = aColor;\n"
"	gl_Position = vec4(aPos , 1.0f);\n"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"uniform float xColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(xColor * ourColor.x, ourColor.y, ourColor.z ,1.0f);\n"
"}\0";

int main()
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a window */
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);

	// check Glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Shader */
	// vertex
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &VertexShaderData, NULL);
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
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &FragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	//Program
	GLuint program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	/* Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* Color Attribute*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		glUniform1f(glGetUniformLocation(program, "xColor"), xValue);

		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
	}

	/* Clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}


