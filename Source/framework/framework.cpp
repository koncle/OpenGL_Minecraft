//
// Created by koncle on 2019/3/17.
//

#include "framework.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* inits(int width, int height) {
    // init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // this code must be called first befor initializing GLAD
    glfwMakeContextCurrent(window);

    // set viewport with window size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
        return nullptr;
    }
    glViewport(0, 0, width, height);

    // capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return window;
}

void start(GLFWwindow* window, void (*func)()) {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        func();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void clearScreen(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}