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
	/* Top Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	/* Bottom Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	/* Left Position */		/* Color */			/* TexCoords */	    	/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	/* Right Position */		/* Color */			/* TexCoords */	   	 /* Normals */
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 /* Back Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f,
	/* Front Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,

};

/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype

unsigned int load_texture(const char* texture_path); // Protype

glm::vec3 to_vec3(float arr[])
{
	glm::vec3 result;

	result.x = arr[0];
	result.y = arr[1];
	result.z = arr[2];

	return result;
}

glm::vec3 cubePositions[] =
{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] =
{
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

/* Light */
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1.5f);


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
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Cube Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position Attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Attribute 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Normals Attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	/* Light Buffers */
	GLuint lightCubeVBO, lightCubeVAO;

	glGenVertexArrays(1, &lightCubeVAO);
	glGenBuffers(1, &lightCubeVBO);

	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Light Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/* Texture */
	GLuint diffuseMap = load_texture("res/Texture/container2.png");
	GLuint specularMap = load_texture("res/Texture/container2_specular.png");

	/* Shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");
	myShader.use();
	myShader.setInt("material.diffuse", 0);
	myShader.setInt("material.specular", 1);

	// Some window
	bool ShowDemo = false;
	bool mySecondWindow = false;
	bool helpWindow = false; // Extra things

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

		float radius = 3.0f;
		float camX = std::sin(time) * radius;
		float camZ = std::cos(time) * radius;

		// Gui Variables
		// Directional Light
		static float dir_direction[3] = { -0.2f, -1.0f, -0.5f };
		static float dir_ambient[3] = { 0.2f, 0.2f ,0.2f };
		static float dir_diffuse[3] = { 0.4f, 0.4f ,0.4f };
		static float dir_specular[3] = { 0.6f, 0.6f ,0.6f };

		// Point Light
		//static float point_position
		static float point_ambient[3] = { 0.2f, 0.2f, 0.2f };
		static float point_diffuse[3] = { 0.5f, 0.5f, 0.5f };
		static float point_specular[3] = { 1.0f, 1.0f, 1.0f };
		static float point_constant = 1.0f;
		static float point_linear = 0.09f;
		static float point_quadratic = 0.032f;

		// Spot Light
		static float spot_ambient[3] = { 0.2f, 0.2f, 0.2f };
		static float spot_diffuse[3] = { 1.0f, 1.0f, 1.0f };
		static float spot_specular[3] = { 1.0f, 1.0f, 1.0f };
		static float spot_constant = 1.0f;
		static float spot_linear = 0.09f;
		static float spot_quadratic = 0.032f;
		static float spot_cutOff = 12.5f;
		static float spot_outerCutOff = 18.5f;

		static float cubeMapPos[3] = { 0.0f, 0.0f, 0.0f };


		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (helpWindow) // Extra things
		{
			ImGui::Begin("How to play ?");
			ImGuiStyle* style = &ImGui::GetStyle();
			style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
			ImGui::Text("HELLO There !");
			ImGui::PopStyleColor();

			ImGui::Text("Move Around with (W-A-S-D-UP-DOWN) key.");
			ImGui::Text("Look Around  with Mouse Button Right and Cursor.");
			ImGui::Text("Turn on Flashlights with Mouse Button Left.");
			ImGui::Text("Zoom out/in with Mouse Scroll.");
			if (ImGui::Button("Thanks!"))
				helpWindow = false;
			ImGui::End();
		}

		// First Object
		myShader.use();

		// Directional Light
		myShader.setVec3("dirLight.direction", to_vec3(dir_direction));
		myShader.setVec3("dirLight.ambient", to_vec3(dir_ambient));
		myShader.setVec3("dirLight.diffuse", to_vec3(dir_diffuse));
		myShader.setVec3("dirLight.specular", to_vec3(dir_specular));

		// Point Lights
		for (int i = 0; i < 4; i++)
		{
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].position").c_str(), pointLightPositions[i] * xValue);
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].ambient").c_str(), to_vec3(point_ambient));
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].diffuse").c_str(), to_vec3(point_diffuse));
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].specular").c_str(), to_vec3(point_specular));
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].constant").c_str(), point_constant);
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].linear").c_str(), point_linear);
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), point_quadratic);
		}

		// Spot Light
		myShader.setVec3("spotLight.position", camera.Position);
		myShader.setVec3("spotLight.direction", camera.Front);
		myShader.setVec3("viewPos", camera.Position);
		myShader.setVec3("spotLight.ambient", to_vec3(spot_ambient));
		myShader.setVec3("spotLight.diffuse", to_vec3(spot_diffuse));
		myShader.setVec3("spotLight.specular", to_vec3(spot_specular));
		myShader.setFloat("spotLight.constant", spot_constant);
		myShader.setFloat("spotLight.linear", spot_linear);
		myShader.setFloat("spotLight.quadratic", spot_quadratic);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(spot_cutOff)));
			myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(spot_outerCutOff)));
		}
		else
		{
			myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(0.0f)));
			myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(0.0f)));

		}

		// Material
		myShader.setFloat("material.shininess", 64.0f);


		/* Coordinates */
		// Projection
		projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		
		// We Draw a map with three loop cuz we are rendering in 3D so each axies need a loop like (x -> i, y -> j, z -> k).
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					// We will set blocks like minecraft and we wannna make it to a hollow huge Maps with 10x10x10 cubes
					if (i == 0 || i == 9 || j == 0 || j == 9 || k == 9)
					{
						// Model
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(i + cubeMapPos[0], j + cubeMapPos[1], k + cubeMapPos[2]));
						//model = glm::rotate(model, glm::radians(-55.0f) * time, glm::vec3(0.0f, 1.0f, 0.0f));

						myShader.setMat4("model", model);
						glBindVertexArray(VAO);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}
				}
			}
		}


		// Second Object
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		lightCubeShader.setVec3("light.ambient", to_vec3(point_ambient));
		lightCubeShader.setVec3("light.diffuse", to_vec3(point_diffuse));

		for (int i = 0; i < 4; i++)
		{
			// Model
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i] * xValue);
			model = glm::scale(model, glm::vec3(0.3f));
			lightCubeShader.setMat4("model", model);
			glBindVertexArray(lightCubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		// Render your GUI
		ImGui::Begin("Light test");

		// Extra things
		ImGuiStyle* style = &ImGui::GetStyle();
		style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
		if (ImGui::Button("Need Helps ?"))	helpWindow = true;
		ImGui::PopStyleColor();

		ImGui::SliderFloat3("Map Position", cubeMapPos, -10.0f, 10.0f);
		ImGui::Text("Directional Light");
		ImGui::SliderFloat3("Directional Direction", dir_direction, -2.0f, 2.0f);
		ImGui::SliderFloat3("Directional Ambient", dir_ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Directional Diffuse", dir_diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Directional Specular", dir_specular, 0.0f, 1.0f);
		ImGui::Text("Point Light");
		ImGui::SliderFloat3("Point Ambient", point_ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Point Diffuse", point_diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Point Specular", point_specular, 0.0f, 1.0f);
		ImGui::SliderFloat("Point Constant", &point_constant, -1.0f, 1.0f);
		ImGui::SliderFloat("Point Linear", &point_linear, -1.0f, 1.0f);
		ImGui::SliderFloat("Point Quadratic", &point_quadratic, -1.0f, 1.0f);
		ImGui::Text("Spot Light");
		ImGui::SliderFloat3("Spot Ambient", spot_ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Spot Diffuse", spot_diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Spot Specular", spot_specular, 0.0f, 1.0f);
		ImGui::SliderFloat("Spot Constant", &spot_constant, -1.0f, 1.0f);
		ImGui::SliderFloat("Spot Linear", &spot_linear, -1.0f, 1.0f);
		ImGui::SliderFloat("Spot Quadratic", &spot_quadratic, -1.0f, 1.0f);
		ImGui::SliderFloat("Spot CutOff", &spot_cutOff, 0.0f, 100.0f);
		ImGui::SliderFloat("Spot OuterCutOff", &spot_outerCutOff, 0.0f, 100.0f);
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


