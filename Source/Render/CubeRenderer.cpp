//
// Created by koncle on 2019/6/11.
//
#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(const char *img_path, const char *vs, const char *fs) : m_Texture(img_path), m_shader_simple(vs, fs) {
    std::vector<GLfloat> texCoords = m_Texture.getTexture("default");
    std::cout << std::endl;

    m_model.addData(
            {
                    //Back
                    1, 0, 0,
                    0, 0, 0,
                    0, 1, 0,
                    1, 1, 0,

                    //Front
                    0, 0, 1,
                    1, 0, 1,
                    1, 1, 1,
                    0, 1, 1,

                    //Right
                    1, 0, 1,
                    1, 0, 0,
                    1, 1, 0,
                    1, 1, 1,

                    //Left
                    0, 0, 0,
                    0, 0, 1,
                    0, 1, 1,
                    0, 1, 0,

                    //Top
                    0, 1, 1,
                    1, 1, 1,
                    1, 1, 0,
                    0, 1, 0,

                    //Bottom
                    0, 0, 0,
                    1, 0, 0,
                    1, 0, 1,
                    0, 0, 1.
            },
            texCoords,
            {
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,

                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,

                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,

                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,

                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,

                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                },
            {
                    // 前
                    0, 1, 2,
                    2, 3, 0,

                    4, 5, 6,
                    6, 7, 4,
//
                    8, 9, 10,
                    10, 11, 8,

                    12, 13, 14,
                    14, 15, 12,

                    16, 17, 18,
                    18, 19, 16,

                    20, 21, 22,
                    22, 23, 20
            }
    );
}

void CubeRenderer::add(glm::vec3 &position) {
    m_quads.push_back(position);
}

void CubeRenderer::render(Player &camera, Shadow &shadow) {
    m_shader.use();

    glActiveTexture(GL_TEXTURE0);
    m_Texture.bindTexture();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadow.getTexture());
    m_model.bindVAO();

    auto ProjViewMatrix = camera.getProjViewMatrix();

    // player setting
    m_shader.setMat4("ProjView", ProjViewMatrix);
    // shadow setting
    m_shader.setMat4("shadowMapSpace", shadow.getLightSpaceMatrix());

    // lights settings
    m_shader.setVec3("lightPos", LIGHT_POS);
    m_shader.setVec3("lightColor", LIGHT_COLOR);
    auto viewPos = camera.position;
    m_shader.setVec3("viewPos", viewPos);

    for (auto &quad : m_quads) {
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, quad);
        m_shader.setMat4("Model", model);
        glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }
    m_model.unbindVAO();
    m_quads.clear();
}

void CubeRenderer::renderShadow(Player &camera, Shadow &shadow) {
    // use shadow shader to render objects
    auto shader = shadow.getShader();
    shader.use();

    // origin objects
    m_Texture.bindTexture();
    m_model.bindVAO();

    shader.setMat4("lightMatrix", shadow.getLightSpaceMatrix());
//    shader.setMat4("lightMatrix", camera.getProjViewMatrix());
    for (auto &quad : m_quads) {
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, quad);
        shader.setMat4("Model", model);
        glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }
    m_model.unbindVAO();
    m_quads.clear();
}

void CubeRenderer::cleanUp() {}

