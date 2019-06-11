#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "glmlib.h"

struct Entity
{
	glm::vec3 cameraPos;
	glm::vec3 cameraFront1;
	glm::vec3 cameraFront2; 
	glm::vec3 cameraUp;
	float fov;
};

#endif // ENTITY_H_INCLUDED
