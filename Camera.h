#pragma once
#include "Vendor/glm/glm/glm.hpp"
#include "Vendor/glm/glm/gtx/transform.hpp"
#include <GLFW/glfw3.h>
#include "KeyInput.h"

class Camera
{
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 worldUp;

	static glm::mat4x4 projection;

	static glm::vec3 direction;
	static float yaw, pitch, lastX, lastY;
	static bool changed;

public:
	Camera(int width, int height);
	void updateVectors();
	static void window_size_callback(GLFWwindow* window, int width, int height);
	glm::mat4x4 getProjectionViewMatrix(glm::vec3 position, float playerHeight);
	glm::vec3 getCameraFrontVector() { return cameraFront; };
	glm::vec3 getCameraRightVector() { return cameraRight; };

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

};

