#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// Directions
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = -0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

using namespace glm;
using namespace std;

class Camera {
public:
	//Camera Attributes
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 WorldUp;
	vec3 Right;

	// Eular Angles
	float Yaw;
	float Pitch;
	//Camera Options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// constructor with vectors
	Camera(vec3 position = vec3(0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		updateCameraVectors();
	}

	mat4 GetViewMatrix()
	{
		return lookAt(this->Position, this->Position + this->Front, this->Up);
	}

	void ProcessMouseMovement(float xoffset, float yoffset)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		if (this->Pitch >= 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch <= -89.0f)
			this->Pitch = -89.0f;

		updateCameraVectors();
	}
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		const float velocity = this->MovementSpeed * deltaTime;
		if (direction == FORWARD)
			this->Position += this->Front * velocity;
		if (direction == BACKWARD)
			this->Position -= this->Front * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == UP)
			this->Position += this->Up * velocity;
		if (direction == DOWN)
			this->Position -= this->Up * velocity;
	}
	void ProcessMouseScroll(float yoffset)
	{
		this->Zoom -= float(yoffset);
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
		if (Zoom <= 20.0f)
			Zoom = 20.0f;
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 direction;
		direction.x = std::cos(glm::radians(this->Yaw)) * std::cos(glm::radians(this->Pitch));
		direction.y = std::sin(glm::radians(this->Pitch));
		direction.z = std::sin(glm::radians(this->Yaw)) * std::cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(direction);

		// Alsom re-calculate for Right and Up vectors
		this->Right = normalize(cross(this->Front, this->WorldUp));
		this->Up = normalize(cross(this->Right, this->Front));
	}
};



