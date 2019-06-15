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

int main() {
    // initialize
    GLFWwindow *window = inits(800, 600);
    if (window == nullptr) {
        return -1;
    }

    World world;
    Player player;
    InputProcessor inputProcessor(player);
    // enable depth test to prevent occulsion
    // only show front image
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    MasterRenderer renderer;
    Shadow shadow;
    GUIEntity crossbar("cross.png", {0, 0}, {0.02, 0.03});
    GUIEntity shadowTexture(shadow.getDepthTexture(), glm::vec3(-0.8, 0.8, 0), glm::vec3(0.2, 0.2, 0));

    Timer timer;
    timer.restartFPS();

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        inputProcessor.handleInput(window, world);
        inputProcessor.update(timer.elapse(), world);

        // used to find a view direction for shadow
        // shadow.changeView(player);

        shadow.bindFrameBuffer();
        renderer.renderWorld(world);
        renderer.finishRenderShadow(player, shadow);

        shadow.unbindFrameBuffer();
        renderer.renderWorld(world);
        renderer.renderGUI(crossbar);
        renderer.renderGUI(shadowTexture);
        renderer.finishRender(player, shadow);

        glfwSwapBuffers(window);
        timer.restart();
        timer.countFPS();

        // std::cout << timer.getFPS() << " FPS" << std::endl;
    }
    // release resource
    glfwTerminate();
    renderer.cleanUp();
    return 0;
}