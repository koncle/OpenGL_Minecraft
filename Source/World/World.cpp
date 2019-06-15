//
// Created by koncle on 2019/6/12.
//

#include "World.h"

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

Entity World::getEntity(int x, int y, int z) {
    if (x < 0 || z < 0 || x >= MAX_WIDTH || z >= MAX_WIDTH) {
        return Entity(glm::vec3(x, y, z), AIR);
    }

    Entity target;
    for (auto &objEntity : map[x][z]) {
        if (objEntity.position.y == y) {
            target = objEntity;
            break;
        }
    }
    if(target.type != -1){
        // return real block
        return target;
    }else{
        // return air
        return Entity(glm::vec3(x, y, z), AIR);
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

        int x = int(std::floor(pos.x));
        int y = int(std::floor(pos.y));
        int z = int(std::floor(pos.z));

        (*adjacentEntities).emplace_back(getEntity(x, y, z));
    }
    return adjacentEntities;
}

void World::addEntity(glm::vec3 pos, int type) {
    pos.x = int(pos.x);
    pos.y = int(pos.y);
    pos.z = int(pos.z);
    if (pos.x < 0 || pos.z < 0 || pos.x >= MAX_WIDTH || pos.z >= MAX_WIDTH) {
        std::cout << "Invalid pos : (" << pos.x << ", " << pos.z << ") !!" << std::endl;
        return;
    }
    auto entity = getEntity(pos.x, pos.y, pos.z);
    if (entity.type == AIR) {
        std::cout << "Add at : (" << pos.x << ", " <<  pos.y << ", " << pos.z << ") !!" << std::endl;
        map[int(pos.x)][int(pos.z)].emplace_back(Entity(pos, type));
    }else{
        std::cout << "Nowhere to put : (" << pos.x << ", " << pos.z << ") !!" << std::endl;
    }
}

void World::removeEntity(glm::vec3 pos) {
    if (pos.x < 0 || pos.z < 0 || pos.x >= MAX_WIDTH || pos.z >= MAX_WIDTH) {
        std::cout << "Invalid pos : (" << pos.x << ", " << pos.z << ") !!" << std::endl;
        return;
    }
    int x = int(pos.x), y = int(pos.y), z= int(pos.z);
        std::vector<Entity> &y_list = map[x][z];
        for (int i = 0; i < y_list.size(); ++i) {
            if(y_list[i].position.y == y){
                y_list.erase(y_list.begin()+i);
                break;
            }
        }
}

std::vector<Entity> **World::getWorldMap() {
    return map;
}

