//
// Created by koncle on 2019/3/31.
//

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "play/Player.h"
#include "Shader/shader.h"
#include "framework/framework.h"
#include "stb_image/stb_image.h"
#include "iostream"
#include "glmlib.h"
#include "Render/MasterRenderer.h"
#include <random>
#include "Utils/Timer.h"
#include "World/World.h"
#include "Shadow/Shadow.h"
#include "play/BlockPicker.h"
#include "play/InputProcessor.h"

class  InputProcessor;
bool intersectPlane(const glm::vec3 &n, const glm::vec3 &p0, const glm::vec3 &l0, const glm::vec3 &l, float &t)
{
    auto n_ = glm::normalize(n);
    auto p0_ = glm::normalize(p0);
    auto l0_ = glm::normalize(l0);
    auto l_  = glm::normalize(l);
    float denom = glm::dot(n_, l_);
    if (denom > 1e-6) {
        auto p0l0 = p0_ - l0_;
        t = glm::dot(p0l0, n_) / denom;
        return (t >= 0);
    }
    return false;
}

void test_intersection(){
    // true : 5.5, 8.5, 3.5
    std::vector<float> myPos = {8.25551, 8.74657, 3.63928};
    std::vector<float> target = {4, 8, 3};
}



int main() {
    // initialize
    GLFWwindow *window = inits(800, 600);
    if (window == nullptr) {
        return -1;
    }

    MasterRenderer renderer;
//    CubeRenderer render("awesomeface.png");

    World world;

    // capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Player player;
    InputProcessor inputProcessor(player);
    // enable depth test to prevent occulsion
    // only show front image
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Timer timer;
    timer.restartFPS();
    glEnable(GL_DEPTH_TEST);
    GUIEntity guiEntity("cross.png", {0, 0}, {0.02, 0.03});
    while (!glfwWindowShouldClose(window)) {

        inputProcessor.handleInput(window, world);
        inputProcessor.update(timer.elapse(), world);

        renderer.renderWorld(world);
        renderer.renderGUI(guiEntity);
        renderer.finishRender(player);

        // -1
        glfwSwapBuffers(window);
        glfwPollEvents();
        timer.restart();
        timer.countFPS();

//        std::cout << timer.getFPS() << " FPS" << std::endl;
    }
    // release resource
    glfwTerminate();
    return 0;
}