//
// Created by koncle on 2019/6/12.
//

#ifndef OPENGLPROJECTS_ENTITY_H
#define OPENGLPROJECTS_ENTITY_H

#include "glhead.h"

class Entity{
public:
    Entity():Entity({-1, -1, -1}, -1){}
    Entity(glm::vec3 position, int type):position(position), type(type){}
    glm::vec3 position;
    int type;
};
#endif //OPENGLPROJECTS_ENTITY_H
