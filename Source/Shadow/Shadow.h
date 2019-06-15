//
// Created by koncle on 2019/6/13.
//

#ifndef OPENGLPROJECTS_SHADOW_H
#define OPENGLPROJECTS_SHADOW_H
#include "glhead.h"
#include "../Shader/shader.h"
#include "../play/Player.h"

class Shadow{
public:
    Shadow();
    ~Shadow();
    void bindFrameBuffer();
    void unbindFrameBuffer();
    unsigned int getTexture();
    unsigned int getDepthTexture();
    glm::mat4 getLightSpaceMatrix();
    Shader& getShader();
    void changeView(Player &player);
    glm::mat4 lightView;
    glm::mat4 lightProjection;
private:
    void smallWindow();
    void generateDepthBuffer();
    void createDepthTextureAttachment(int width, int height);
    void createTextureAttachment(int width, int height);
    void createDepthBufferAttachment(int width, int height);
    unsigned int framebuffer;
    unsigned int rbo;
    unsigned int depthMap;
    unsigned int texture;
    Shader shader;
    glm::mat4 lightSpaceMatrix;
};
#endif //OPENGLPROJECTS_SHADOW_H
