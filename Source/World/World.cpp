//
// Created by koncle on 2019/6/12.
//

#include "World.h"
#include <iostream>

World::World() {
    generateWorld();
}

void World::generateWorld() {
    map = new std::vector<Entity>*[MAX_WIDTH];
    for(uint i = 0; i < MAX_WIDTH; ++i){
        map[i] = new std::vector<Entity>[MAX_WIDTH];
        for (uint j = 0; j < MAX_WIDTH; ++j){
            auto a = glm::vec3(1,2,3);
            auto height = std::rand()%(MAX_LEVEL-2) + 2;
            map[i][j] = std::vector<Entity>();
            map[i][j].emplace_back(Entity(glm::vec3(i, height, j), GRASS));
            for (int k = MIN_LEVEL; k < height; ++k) {
                map[i][j].emplace_back(Entity(glm::vec3(i, k, j), GROUND));
            }
        }
    }
}

void World::render(Renderer& renderer) {
    for(uint i = 0; i < MAX_WIDTH; ++i){
        for(uint j = 0; j < MAX_WIDTH; ++j){
            auto vector = map[i][j];
            for(auto &entity :vector ){
                if(entity.position.y > MIN_LEVEL) {
                    renderer.add(entity.position);
                }
            }
        }
    }
}

std::vector<Entity>* World::getAdjacentEntities(Entity& entity) {
    auto position = entity.position;
    auto adjacentEntities = new std::vector<Entity>();
    std::vector<glm::vec3> adjacents = {
            {0, 0, -1}, // back
            {0, 0, 1},  // front
            {-1, 0, 0}, // left
            {1, 0, 0}, // left
            {0, -1, 0}, // bot
            {0, 1, 0}, // top
    };
    for(auto &pos : adjacents) {
        pos = pos + position;
        int x = std::floor(pos.x);
        int y = std::floor(pos.y);
        int z = std::floor(pos.z);

        if (x < 0 || z < 0 || x >= MAX_WIDTH || z >= MAX_WIDTH) {
            (*adjacentEntities).push_back(Entity(pos, AIR));
            continue;
        }

        bool find = false;
        for (auto &objEntity : map[x][z]) {
            if (objEntity.position.y == y) {
                (*adjacentEntities).push_back(objEntity);
                find = true;
                break;
            }
        }
        // return air entity if not found;
        if (!find) (*adjacentEntities).push_back(Entity(pos, AIR));
    }
    return adjacentEntities;
}
