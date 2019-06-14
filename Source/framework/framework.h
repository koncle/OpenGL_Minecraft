//
// Created by koncle on 2019/3/17.
//

#ifndef OPENGLPROJECTS_FRAMEWORK_H
#define OPENGLPROJECTS_FRAMEWORK_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "assert.h"

void processInput(GLFWwindow *window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* inits(int width, int height);

void start(GLFWwindow* window, void (*func)());

void clearScreen();

#endif //OPENGLPROJECTS_FRAMEWORK_H