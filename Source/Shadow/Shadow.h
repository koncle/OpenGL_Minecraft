//
// Created by koncle on 2019/6/13.
//

#ifndef OPENGLPROJECTS_SHADOW_H
#define OPENGLPROJECTS_SHADOW_H
#include "glhead.h"
#include "../Shader/Shader.h"

class Shadow{
public:
    Shadow(){generateDepthBuffer();}
    ~Shadow();
    void bindFrameBuffer();
    void unbindFrameBuffer();
    void use(Shader& shader);

private:
    void generateDepthBuffer();
    unsigned int framebuffer;
    unsigned int rbo;
    unsigned int depthMap;
};
#endif //OPENGLPROJECTS_SHADOW_H
