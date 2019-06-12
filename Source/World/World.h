//
// Created by koncle on 2019/6/12.
//

#ifndef OPENGLPROJECTS_WORLD_H
#define OPENGLPROJECTS_WORLD_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glmlib.h"
#include "Constants.h"
#include <iostream>
#include "../Render/Renderer.h"
#include <vector>
class Renderer;

class World{
public:
    World();
    void render(Renderer& renderer);
    std::vector<Entity>* getAdjacentEntities(Entity& entity);

private:
    void generateWorld();

    std::vector<Entity>** map;
};
#endif //OPENGLPROJECTS_WORLD_H
