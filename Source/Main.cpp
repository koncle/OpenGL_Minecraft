//
// Created by koncle on 2019/3/31.
//
#include "World/Player.h"
#include "Shader/shader.h"
#include "framework.h"
#include "stb_image/stb_image.h"
#include "iostream"
#include "glmlib.h"
#include "Render/Renderer.h"
#include <random>
#include "Utils/Timer.h"
#include "World/World.h"

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

    Renderer renderer("DefaultPack.png");
//    Renderer render("awesomeface.png");
    for (int i = 0; i <3; ++i) {
        renderer.add(cubePositions[i]);
    }

    World world;

    // capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Player player;

    // enable depth test to prevent occulsion
    glEnable(GL_DEPTH_TEST);
    // only show front image
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Timer timer;
    timer.restartFPS();
    while (!glfwWindowShouldClose(window)) {
        player.handleInput(window);
        player.update(timer.elapse(), world);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        world.render(renderer);
        renderer.render(player);

        glfwSwapBuffers(window);
        glfwPollEvents();
        timer.restart();
        timer.countFPS();
        std::cout << timer.getFPS() << " FPS" << std::endl;
    }

    // release resource
    glfwTerminate();
    return 0;
}