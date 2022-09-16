#include "Camera.h"


glm::mat4x4 Camera::projection;

// static fields necessary for callback function
glm::vec3 Camera::direction;
float Camera::yaw, Camera::pitch, Camera::lastX, Camera::lastY;
bool Camera::changed;

void Camera::updateVectors()
{
    // set camera vectors based on where the character is looking at
    if (this->changed)
    {
        cameraFront = glm::normalize(direction);
        cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
        cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
        this->changed = false;
    }
}

void Camera::window_size_callback(GLFWwindow* window, int width, int height)
{
    projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 200.0f);
}

Camera::Camera(int width, int height)
{
    // initial direction
    cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    worldUp = cameraUp;
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));

    yaw = 90.0f;
    pitch = 0.0f;
    changed = false;


    projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 200.0f);
}


glm::mat4x4 Camera::getProjectionViewMatrix(glm::vec3 position, float playerHeight)
{
    // offset for player height
    position = { position.x, position.y + playerHeight, position.z };
    return projection * glm::lookAt(position, position + cameraFront, cameraUp);
}


void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // first mouse - first time the position gets updated - when the program is first run
    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    const float sensitivity = 0.1f;

    // get the offset
    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity;
    lastX = xpos;
    lastY = ypos;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;

    if (pitch < -89.0f)
        pitch = -89.0f;

    // get a new pointing direction vector
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    changed = true;
}


