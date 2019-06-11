//
// Created by koncle on 2019/3/31.
//
#include "Player/Player.h"
#include "Shader/shader.h"
#include "framework.h"
#include "stb_image/stb_image.h"
#include "iostream"
#include "glmlib.h"
#include "camera.h"
#include "Render/Renderer.h"

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
};

int main() {
    // initialize
    GLFWwindow *window = inits(800, 600);
    if (window == nullptr) {
        return -1;
    }

    Renderer render("awesomeface.png");
    for (unsigned int i = 0; i < 5; i++) {
        render.add(cubePositions[i]);
    }

    Player player;
    // enable depth test to prevent occulsion
    glEnable(GL_DEPTH_TEST);
    // capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window)) {
        player.handleInput(window);
        player.update(0.1f);

        render.render(player);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // release resource
    glfwTerminate();
    return 0;
}