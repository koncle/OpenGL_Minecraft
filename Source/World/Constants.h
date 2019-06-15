//
// Created by koncle on 2019/6/12.
//

#ifndef OPENGLPROJECTS_CONSTANTS_H
#define OPENGLPROJECTS_CONSTANTS_H

#include <glhead.h>
constexpr int PLAYER = -1,  AIR = 0, GROUND = 1, GRASS  = 2;

#define MAX_WIDTH 20
#define MIN_LEVEL 0
#define MAX_LEVEL 10
#define uint unsigned int

#define ENTITY_SIZE 1.f

const glm::vec3 LIGHT_POS(-7.70095, 21.3573, -5.7789);
const glm::vec3 LIGHT_DIR(0.745144, -0.372178, 0.553393);
const glm::vec3 LIGHT_COLOR(1, 1, 1);

#endif //OPENGLPROJECTS_CONSTANTS_H
