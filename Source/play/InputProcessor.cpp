//
// Created by koncle on 2019/6/14.
//
#include "InputProcessor.h"

void InputProcessor::update(float dt, World &world) {
    player.update(dt, world);
}

void InputProcessor::handleInput(GLFWwindow* window, World& world)
{
    player.handleInput(window);

    keyboardInput(window, world);
    mouseInput(window, world);
}

void InputProcessor::keyboardInput(GLFWwindow* window, World& world){}

void InputProcessor::mouseInput(GLFWwindow* window, World& world)
{
    if(mouseTimer.elapse() > MOUSE_RESTRICT_TIME) {
        // click event
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            auto blockPos = blockPicker.getAroundBlock(window, world);
            if (blockPos.x == -1) return;
            world.addEntity(blockPos, GRASS);
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            auto blockPos = blockPicker.getDirectBlock(window, world);
            if (blockPos.x == -1) return;
            world.removeEntity(blockPos);
        }
        mouseTimer.restart();
    }
}
