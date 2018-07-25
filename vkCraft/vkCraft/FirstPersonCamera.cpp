#pragma once

#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.cpp"

class FirstPersonCamera : public Camera
{
public:
	/**
	 * Camera orientation vector, x is horizontal orientation and y is vertical orientation.
	 */
	glm::vec2 orientation;

	/**
	 * Stores last mouse position.
	 */
	glm::vec2 last;
	
	/**
	 * Mouse movement delta.
	 */
	glm::vec2 delta;

	FirstPersonCamera()
	{
		position.z = 5.0f;
	}

	/**
	 * Update the camera movement from user input.
	 */
	void update(GLFWwindow *window, double time)
	{
		float moveSpeed = 5.0f * time;
		float lookSpeed = 0.4f * time;

		float pi = 3.14159265359f;
		float pid2 = pi / 2.0f;
		
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

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			position.y += moveSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		{
			position.y -= moveSpeed;
		}

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		delta.x = x - last.x;
		delta.y = y - last.y;
		last.x = x;
		last.y = y;

		//Update mouse cursor
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			orientation.x -= delta.x * lookSpeed;
			orientation.y -= delta.y * lookSpeed;
		}

		//Camera orientation
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			orientation.x += lookSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			orientation.x -= lookSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			orientation.y += lookSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			orientation.y -= lookSpeed;
		}
		
		//std::cout << "Hor:" << orientation.x << " Ver:" << orientation.y << std::endl;

		//Limit vertical orientation
		if(orientation.y < -1.57f)
		{
			orientation.y = -1.57f;
		}
		else if(orientation.y > 1.57f)
		{
			orientation.y = 1.57f;
		}
		
		updateMatrix();
	}

	/**
	 * Update the camera matrix.
	 * 
	 * Consider the camera orientation and translation only.
	 */
	void updateMatrix()
	{
		matrix = glm::translate(glm::mat4(), position);
		matrix = glm::rotate(matrix, orientation.x, glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, orientation.y, glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::inverse(matrix);
	}
};
