//
// Created by koncle on 2019/6/14.
//

#ifndef OPENGLPROJECTS_INPUTPROCESSOR_H
#define OPENGLPROJECTS_INPUTPROCESSOR_H

#include "../Collision/AABB.h"
#include "../World/Constants.h"

#include "../World/World.h"
#include "Player.h"
#include "BlockPicker.h"
#include "../Utils/Timer.h"

class BlockPicker;

class InputProcessor{
public:
    InputProcessor(Player &player):player(player), blockPicker(player){}
    void handleInput(GLFWwindow * window, World& world);
    void update(float dt, World& world);

private:
    void keyboardInput(GLFWwindow * window, World& world);
    void mouseInput(GLFWwindow * window, World& world);

    Player &player;
    BlockPicker blockPicker;
    Timer mouseTimer;

    // restrict the mouse click frequency.
    float MOUSE_RESTRICT_TIME = 0.1;

};
#endif //OPENGLPROJECTS_INPUTPROCESSOR_H
