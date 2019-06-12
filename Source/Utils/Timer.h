//
// Created by koncle on 2019/6/10.
//

#ifndef OPENGLPROJECTS_TIMER_H
#define OPENGLPROJECTS_TIMER_H

#include <GLFW/glfw3.h>

class Timer{
public:
    void restart();
    float elapse();
    void restartFPS();
    void countFPS();
    float getFPS();

private:
    float time=0;
    float fps_start_time=0;
    float fps=0;
};

#endif //OPENGLPROJECTS_TIMER_H
