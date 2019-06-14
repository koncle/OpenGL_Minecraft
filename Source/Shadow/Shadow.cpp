//
// Created by koncle on 2019/6/13.
//

#include "Shadow.h"

void Shadow::generateDepthBuffer() {
    // framebuffer
    glGenFramebuffers(1, &framebuffer);

    // create a color attachment texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // attach texture to framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow::bindFrameBuffer() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, 800, 600);
}

void Shadow::unbindFrameBuffer(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Shadow::~Shadow() {
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &depthMap);
}

void Shadow::use(Shader &shader) {
    GLfloat near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f), glm::vec3(1.0));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    shader.setMat4("lightMat", lightSpaceMatrix);
}
