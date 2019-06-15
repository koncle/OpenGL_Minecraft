//
// Created by koncle on 2019/6/13.
//

#include "Shadow.h"

void Shadow::generateDepthBuffer() {
//    smallWindow();
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap, 0);
    glDrawBuffer(GL_NONE);
    // glReadBuffer(GL_NONE);
    createTextureAttachment(800, 600);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Shadow::smallWindow(){
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    createTextureAttachment(800, 600);
    createDepthBufferAttachment(800, 600);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    depthMap = texture;
}

void Shadow::createTextureAttachment(int width, int height){
    // create a color attachment texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

// 将它附加到当前绑定的帧缓冲对象
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
}

void Shadow::createDepthBufferAttachment(int width, int height){
    // create a color attachment texture
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void Shadow::bindFrameBuffer() {
    glViewport(0, 0, 1024, 1024);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void Shadow::unbindFrameBuffer(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 800, 600);
}

Shadow::~Shadow() {
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &depthMap);
    glDeleteTextures(1, &texture);
}

unsigned int Shadow::getTexture() {
    return texture;
}

unsigned int Shadow::getDepthTexture() {
    return depthMap;
}

void Shadow::changeView(Player &player){
    lightView = player.getViewMatrix();
    lightSpaceMatrix = lightProjection * lightView;
}

Shadow::Shadow() : shader("shadow.vs", "shadow.fs"){
    generateDepthBuffer();
    lightProjection = glm::ortho(-5.0f, 30.0f, 30.0f, -5.0f, -5.f, 40.f);
    lightView = glm::lookAt(LIGHT_POS, LIGHT_POS+LIGHT_DIR, glm::vec3(0, 1, 0));
    lightSpaceMatrix = lightProjection * lightView;
}

glm::mat4 Shadow::getLightSpaceMatrix() {
    return lightSpaceMatrix;
}

Shader &Shadow::getShader() {
    return shader;
}

