#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.cpp"

class FirstPersonCamera : public Camera
{
public:
	glm::vec2 orientation;

	void update(GLFWwindow *window, float time = 0.01f)
	{
		float moveSpeed = 2.0f * time;
		float lookSpeed = 1.0f * time;
		float pi = 3.14f;
		float pid2 = 1.57f;

		//Camera move
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			position.z -= moveSpeed * std::cos(orientation.x);
			position.x -= moveSpeed * std::sin(orientation.x);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			position.z += moveSpeed * std::cos(orientation.x);
			position.x += moveSpeed * std::sin(orientation.x);
		}

		float lateral = orientation.x + pid2;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			position.z += moveSpeed * std::cos(lateral);
			position.x += moveSpeed * std::sin(lateral);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			position.z -= moveSpeed * std::cos(lateral);
			position.x -= moveSpeed * std::sin(lateral);
		}

		//Get cursor position
		//glfwGetCursorPos

		//Camera orientation
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			orientation.x -= lookSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			orientation.x += lookSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			orientation.y += lookSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			orientation.y -= lookSpeed;
		}
		
		//Limit vertical orientation
		if(orientation.y < -1.57)
		{
			orientation.y = -1.57;
		}
		else if(orientation.y > 1.57)
		{
			orientation.y = 1.57;
		}

		//Calculate camera orientation
		float cos = std::cos(orientation.y);
		glm::vec3 direction = glm::vec3(std::sin(orientation.x + pi) * cos, std::sin(orientation.y), std::cos(orientation.x + pi) * cos);
		direction += position;
		//lookAtDirection(direction);
		
		updateMatrix();
	}

	void lookAtDirection(glm::vec3 direction)
	{
		//this.inverseTransformationMatrix.lookAt(this.position, direction, Camera.UP);
		//this.inverseTransformationMatrix.setPosition(this.position);
		//this.transformationMatrix.getInverse(this.inverseTransformationMatrix);
	};
};
