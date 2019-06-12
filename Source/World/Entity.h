//
// Created by koncle on 2019/6/12.
//

#ifndef OPENGLPROJECTS_ENTITY_H
#define OPENGLPROJECTS_ENTITY_H

class Entity{
public:
    Entity():Entity({0, 0, 0}, 0){}
    Entity(glm::vec3 position, int type):position(position), type(type){}
    glm::vec3 position;
    int type;
};
#endif //OPENGLPROJECTS_ENTITY_H
