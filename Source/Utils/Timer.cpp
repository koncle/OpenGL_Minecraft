//
// Created by koncle on 2019/6/10.
//
#include "Timer.h"

float Timer::elapse(){
    auto current_time =  static_cast<float>(glfwGetTime());
    return current_time - time;
}

void Timer::restart() {
    time = static_cast<float>(glfwGetTime());
}

void Timer::restartFPS() {
    fps_start_time = static_cast<float>(glfwGetTime());
    fps = 0;
}

void Timer::countFPS() {
    fps += 1;
}

float Timer::getFPS() {
    auto elapsed_time = static_cast<float>(glfwGetTime()) - fps_start_time;
    return fps / elapsed_time;
}
