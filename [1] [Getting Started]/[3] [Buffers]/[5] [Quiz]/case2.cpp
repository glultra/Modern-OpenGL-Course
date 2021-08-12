#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

float vertices[] = 
{ 
	/* Position */
	-0.5f, -0.5f, 0.0f, // Bottom Left
	 0.5f, -0.5f, 0.0f, // Bottom Right
	 0.7f,  0.0f, 0.0f, // Middile Right
	 0.5f,  0.5f, 0.0f, // Top Right
	-0.5f,  0.5f, 0.0f, // Top Left
	-0.7f,  0.0f, 0.0f, // Middile Left
};


int indecies[] =
{
	0,1,2,
	2,3,4,
	4,5,0
};



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

	/* Buffers */
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), &indecies, GL_STATIC_DRAW);

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

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, 0);
		 // NOTE: You should use GL_TRIANGLE_FAN to fill the shape that's inside the hexagon.

		// Display 
		glfwSwapBuffers(window);

		// Pollevents
		glfwPollEvents();
	}

	/* Clear */
	glfwDestroyWindow(window);
	glfwTerminate();
}
