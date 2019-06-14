#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "glhead.h"
#include "../World/Entity.h"
#include "../Collision/AABB.h"
#include "../Utils/Timer.h"
#include "../World/Constants.h"
#include "../World/World.h"

class Player : public Entity
{
    public:
        Player();

		void handleInput(GLFWwindow * window);

        void update(float dt, World& world);
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        glm::mat4 getProjViewMatrix();

    private:
		void keyboardInput(GLFWwindow * window);
		void mouseInput(GLFWwindow * window);

		glm::vec3 m_velocity = glm::vec3(0.f);

        glm::vec3 cameraFront1;
        glm::vec3 cameraUp;
        float fov;

		bool firstMouse;
		float yaw ;
		float pitch;
		float lastX;
		float lastY;
		float speed;

		float gravity;
		bool gravity_on;

		Timer jump_timer;
		bool jump_start=false;
	    float jump_duration;
	    float jump_height;
};



#endif // PLAYER_H_INCLUDED
