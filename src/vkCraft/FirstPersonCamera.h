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

#include "Camera.h"

/**
 * A camera that can be controlled for FPS views.
 */
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

	FirstPersonCamera();

	/**
	 * Update the camera movement from user input.
	 */
	void update(GLFWwindow *window, double time);

	/**
	 * Update the camera matrix.
	 *
	 * Consider the camera orientation and translation only.
	 */
	void updateMatrix();
};
