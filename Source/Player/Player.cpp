#include "Player.h"
#include<iostream>

Player::Player()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	cameraFront1 = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraFront2 = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	fov = 45.0f;

	firstMouse = true;
	yaw = -90.0f;
	pitch = 0.0f;
	lastX = 800.0f / 2.0;
	lastY = 600.0 / 2.0;
}

void Player::handleInput(GLFWwindow* window)
{
    keyboardInput(window);
    mouseInput(window);
}

void Player::update(float dt)
{
	float cameraSpeed = 0.01;
    cameraPos += m_velocity * cameraSpeed;
	std::cout << cameraPos.x << " "<< cameraPos.y << " " << cameraPos.z << std::endl;
	m_velocity = glm::vec3(0.f);
}

void Player::keyboardInput(GLFWwindow* window)
{
    glm::vec3 change=glm::vec3(0.f);
    float speed = 0.5;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		change +=  cameraFront1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		change -=  cameraFront1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		change -= glm::normalize(glm::cross(cameraFront1, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		change += glm::normalize(glm::cross(cameraFront1, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		change += (glm::vec3(0.0f, 1.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		change -= (glm::vec3(0.0f, 1.0f, 0.0f));

	std::cout << change.x << " "<< change.y << " " << change.z << std::endl;
    m_velocity += change;
}

void Player::mouseInput(GLFWwindow* window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (firstMouse)
	{
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}

	float xoffset = static_cast<float>(xpos - lastX);
	float yoffset = static_cast<float>(lastY - ypos); 

	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// it only cause restriction
    //	if (yaw > 45)
    //		yaw = 45;

	cameraFront1.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraFront1.y = sin(glm::radians(pitch));
	cameraFront1.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront1 = glm::normalize(cameraFront1);
}


glm::mat4 Player::getViewMatrix() {
	return glm::lookAt(cameraPos, cameraPos + cameraFront1, cameraUp);
}

glm::mat4 Player::getProjectionMatrix() {
	return glm::perspective(glm::radians(fov), (600.f / 800.f), 0.1f, 100.0f);
}

glm::mat4 Player::getProjViewMatrix() {
	auto view = getViewMatrix();
	auto proj = getProjectionMatrix();
	return proj * view;
}




























