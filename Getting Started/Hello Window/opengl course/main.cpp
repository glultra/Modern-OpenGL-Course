#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


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

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{
		/* Update */

		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		// Display 
		glfwSwapBuffers(window);

		// Pollevents
		glfwPollEvents();
	}

	/* Clear */
	glfwDestroyWindow(window);
	glfwTerminate();
}
