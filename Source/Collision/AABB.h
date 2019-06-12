//
// Created by koncle on 2019/6/12.
//

#ifndef OPENGLPROJECTS_AABB_H
#define OPENGLPROJECTS_AABB_H

#include "../World/Entity.h"
#include "../World/Constants.h"

class AABB{
public:
    static bool hit(Entity& entity, Entity& obj){
        // obj is the player, it is a point, so its position represents its center position,
        // use this position as the center of the box to test the collision.
        auto position1 = entity.position;
        auto position2 = obj.position;
        return (position1.x < position2.x + ENTITY_SIZE/2. && position1.x + ENTITY_SIZE > position2.x - ENTITY_SIZE / 2.) &&
               (position1.y < position2.y + ENTITY_SIZE/2. && position1.y + ENTITY_SIZE > position2.y - ENTITY_SIZE / 2.) &&
               (position1.z < position2.z + ENTITY_SIZE/2. && position1.z + ENTITY_SIZE > position2.z - ENTITY_SIZE / 2.);
    }
};
#endif //OPENGLPROJECTS_AABB_H
