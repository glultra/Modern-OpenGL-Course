#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

float vertices[] =
{
	/* Position */
	-0.5f, -0.5f, 0.0f, // Bottom Left
	 0.5f, -0.5f, 0.0f, // Bottom Right
	 0.5f,  0.5f, 0.0f, // Top Right

	 0.5f,  0.5f, 0.0f, // Top Right
	-0.5f,  0.5f, 0.0f, // Top Left
	-0.5f, -0.5f, 0.0f, // Bottom Left
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0f);\n"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.31f, 1.0f);\n"
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

	// Create a window
	GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);

	// Check Glew
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
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << ">" << std::endl;
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
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	
	/* Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{
		/* Update */

		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// Display 
		glfwSwapBuffers(window);

		// Pollevents
		glfwPollEvents();
	}

	/* Clear */
	glfwDestroyWindow(window);
	glfwTerminate();
}
