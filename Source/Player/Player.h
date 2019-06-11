#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "glad/glad.h"
#include "Entity.h"
#include "GLFW/glfw3.h"
#include "glmlib.h"

class Player : public Entity
{
    public:
        Player();

		void handleInput(GLFWwindow * window);

        void update(float dt);
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        glm::mat4 getProjViewMatrix();

    private:
		void keyboardInput(GLFWwindow * window);
		void mouseInput(GLFWwindow * window);

		glm::vec3 m_velocity = glm::vec3(0.f);

		bool firstMouse;
		float yaw ;
		float pitch;
		float lastX;
		float lastY;
};



#endif // PLAYER_H_INCLUDED
