#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define SCR_WIDTH 1000
#define SCR_HEIGHT 800
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 330"

float vertices[] =
{
	/* Top Position */		/* Color */				/* TexCoords */
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	/* Bottom Position */	/* Color */				/* TexCoords */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	/* Left Position */		/* Color */				/* TexCoords */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	/* Right Position */	/* Color */				/* TexCoords */
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 /* Back Position */	/* Color */				/* TexCoords */
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	/* Front Position */	/* Color */				/* TexCoords */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,

};

/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype
unsigned int load_texture(const char* texture_path); // Protype

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;


/* Frames */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Camera */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);
	//glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	// check Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Options */
	glEnable(GL_DEPTH_TEST);

	/* ImGui */
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "test2.ini";
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* Color Attribute*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* Texture Attribute */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/* Texture */
	stbi_set_flip_vertically_on_load(true);
	unsigned int container_texture = load_texture("res/Texture/container.jpg");
	unsigned int face_texture = load_texture("res/Texture/awesomeface.png");
	GLuint pyramid_texture = load_texture("res/Texture/pyramid.jpg");

	/* Shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	myShader.use();
	myShader.setInt("container_texture", 0);
	myShader.setInt("face_texture", 1);
	myShader.setInt("pyramid_texture", 2);

	// Some window
	bool ShowDemo = false;
	bool mySecondWindow = false;

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		userInput(window);
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		float radius = 5.0f;
		float camX = std::sin(time) * radius;
		float camZ = std::cos(time) * radius;

		// Gui Variables
		static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
		static float color_value[3] = { 1.0f,1.0f,1.0f };
		static float rotate_value[3] = { 1.0f, 1.0f, 1.0f };
		static float angle = -55.0f;
		static bool isTexture = false;
		static bool isColor = false;
		static float alpha = 0.2f;

		myShader.setVec3("colors", color_value[0], color_value[1], color_value[2]);
		myShader.setBool("isTexture", isTexture);
		myShader.setBool("isColor", isColor);
		myShader.setFloat("alpha", alpha);

		/* Coordinates */
		// Projection
		projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		// Model
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scale_value[0], scale_value[1], scale_value[2]));
		model = glm::rotate(model, glm::radians(-55.0f) * angle, glm::vec3(rotate_value[0], rotate_value[1], rotate_value[2]));
		myShader.setMat4("model", model);

		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ShowDemo)
			ImGui::ShowDemoWindow(&ShowDemo);
		if (mySecondWindow)
		{
			ImGui::Begin("GUI 2");
			ImGui::Text("Hey im a window here.");
			if (ImGui::Button("close me"))
				mySecondWindow = false;
			ImGui::End();
		}

		myShader.use();

		glBindVertexArray(VAO);
		glLineWidth(10.0f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, container_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, face_texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Render your GUI
		float FPS = ImGui::GetIO().Framerate;
		ImGui::Begin("GUI");
		ImGui::Text("FPS = %f", FPS);
		ImGui::Checkbox("Texture", &isTexture);
		ImGui::Checkbox("Color", &isColor);
		ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);
		+ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
		+ImGui::SliderFloat3("Rotate", rotate_value, 0.01f, 1.0f);
		ImGui::SliderAngle("Angle", &angle);
		ImGui::ColorEdit3("Color", color_value);
		if (ImGui::Button("Demo"))
		{
			ShowDemo = true;
		}
		if (ImGui::Button("Window"))
		{
			mySecondWindow = true;
		}
		ImGui::End();

		// Render to screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	const float camera_speed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // To exit the program
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

}
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	if (isFirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}
