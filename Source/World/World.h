//
// Created by koncle on 2019/6/12.
//

#ifndef OPENGLPROJECTS_WORLD_H
#define OPENGLPROJECTS_WORLD_H

#include <glhead.h>
#include "Constants.h"
#include "Entity.h"

class World{
public:
    World();
    Entity getEntity(int x, int y, int z);
    void addEntity(glm::vec3 pos, int type);
    void removeEntity(glm::vec3 pos);
    std::vector<Entity>* getAdjacentEntities(Entity& entity);
    std::vector<Entity>** getWorldMap();
private:
    void generateWorld();

    std::vector<Entity>** map;
};
#endif //OPENGLPROJECTS_WORLD_H
