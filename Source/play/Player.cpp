#include "Player.h"
#include "../Utils/Timer.h"

void show(glm::vec3 &a){
	std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ")" << std::endl;
}
void show(glm::vec4 &a){
	std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ", " << a.w << ")" << std::endl;
}

Player::Player()
{
	position = glm::vec3(-1.0f, 10.0f, -1.0f);
	cameraFront1 = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	fov = 45.0f;

	firstMouse = true;
	yaw = -90.0f;
	pitch = 0.0f;
	lastX = 800.0f / 2.f;
	lastY = 600.0f / 2.f;
	speed = 1.f;

	// gravity is 1, jump height should big than this to jump.
	gravity = 1;
	gravity_on = false;
	jump_duration = 1.;
	jump_height = 3;
	m_velocity = glm::vec3(0.f);
}

void Player::handleInput(GLFWwindow* window)
{
    keyboardInput(window);
    mouseInput(window);
}

void Player::update(float dt, World& world)
{
	float cameraSpeed = 0.001f*speed;
	position += m_velocity * cameraSpeed;
	// std::cout <<"pos"; show(position); std::cout << "front"; show(cameraFront1);
    // show(m_velocity);
	std::vector<Entity>* adjacentEntities = world.getAdjacentEntities(*this);
	for (int i = 0; i < (*adjacentEntities).size(); ++i) {
		Entity entity = (*adjacentEntities)[i];
		if (entity.type == AIR){
			continue;
		}
		if(AABB::hit(entity, *this)){
			// std::cout << "hit!"<< std::endl;
			switch (i){
				// extra size to prevent no render for very close cube.
				// It also can prevent some collision bugs.
				case 0:position.z = entity.position.z + ENTITY_SIZE * 1.5;break;
				case 1:position.z = entity.position.z - ENTITY_SIZE * 0.5;break;
				case 2:position.x = entity.position.x + ENTITY_SIZE * 1.5;break;
				case 3:position.x = entity.position.x - ENTITY_SIZE * 0.5;break;
				case 4:position.y = entity.position.y + ENTITY_SIZE * 1.5;break;
				case 5:position.y = entity.position.y - ENTITY_SIZE * 0.5;break;
				default:break;
			}
		}
	}
}

/*
 * This function only support process one key a time.
 * */
void Player::keyboardInput(GLFWwindow* window)
{
    glm::vec3 change=glm::vec3(0.f);
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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if(gravity_on){
			// if in gravity mode, player can jump,
			if(!jump_start) {
				jump_start = true;
				// use a timer to record jump duration.
				jump_timer.restart();
			}
		}else {
			// normal mode, no jump
			change += glm::vec3(0.0f, 1.0f, 0.0f);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		change -= (glm::vec3(0.0f, 1.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		gravity_on = !gravity_on;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		speed += 0.5;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		speed -= 0.5;
		if(speed < 1.f) speed = 1;
	}
	if(gravity_on){
		change.y -= gravity;

		if(jump_start) {
			change.y += (1 - jump_timer.elapse() / jump_duration) * jump_height;
			if (jump_timer.elapse() >= jump_duration) {
				jump_start = false;
			}
		}
	}
	// momentum
	m_velocity *= 0.95;
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

	cameraFront1.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraFront1.y = sin(glm::radians(pitch));
	cameraFront1.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront1 = glm::normalize(cameraFront1);
}


glm::mat4 Player::getViewMatrix() {
	return glm::lookAt(position, position + cameraFront1, cameraUp);
}

glm::mat4 Player::getProjectionMatrix() {
	return glm::perspective(glm::radians(fov), (800.f / 600.f), 0.1f, 100.0f);
//	return glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.f, 1.0f);
}

glm::mat4 Player::getProjViewMatrix() {
	auto view = getViewMatrix();
	auto proj = getProjectionMatrix();
	return proj * view;
}