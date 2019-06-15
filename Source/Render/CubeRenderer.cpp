//
// Created by koncle on 2019/6/11.
//
#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(const char *img_path, const char *vs, const char *fs) : m_Texture(img_path) {
    const std::vector<GLfloat > vertice =   {
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
    };
    const std::vector<GLuint> indice = {
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
    };
    const std::vector<GLfloat> norms =  {
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
    };
    const std::vector<GLfloat> grass_texture = m_Texture.getTexture(GRASS);
    const std::vector<GLfloat> ground_texture = m_Texture.getTexture(GROUND);
    grass_model.addData(vertice, grass_texture, norms, indice);
    ground_model.addData(vertice, ground_texture, norms, indice);
}

void CubeRenderer::add(Entity &entity) {
    m_quads.push_back(entity);
}

void CubeRenderer::render(Player &camera, Shadow &shadow) {
    m_shader.use();

    glActiveTexture(GL_TEXTURE0);
    m_Texture.bindTexture();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadow.getTexture());

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
        switch (quad.type){
            case GRASS:
                grass_model.bindVAO();
                break;
            case GROUND:
                ground_model.bindVAO();
                break;
            default:
                std::cout << "wrong type"<< quad.type << std::endl;
        }
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, quad.position);
        m_shader.setMat4("Model", model);
        glDrawElements(GL_TRIANGLES, grass_model.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }
    grass_model.unbindVAO();
    m_quads.clear();
}

void CubeRenderer::renderShadow(Player &camera, Shadow &shadow) {
    m_Texture.bindTexture();

    // use & use shadow shader to render objects
    Shader &shader = shadow.getShader();
    shader.use();
    shader.setMat4("lightMatrix", shadow.getLightSpaceMatrix());
    // shader.setMat4("lightMatrix", camera.getProjViewMatrix());
    for (auto &quad : m_quads) {
        switch (quad.type){
            case GRASS:
                grass_model.bindVAO();
                break;
            case GROUND:
                ground_model.bindVAO();
                break;
            default:
                std::cout << "wrong type" << std::endl;
        }
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, quad.position);
        shader.setMat4("Model", model);
        glDrawElements(GL_TRIANGLES, grass_model.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }
    grass_model.unbindVAO();
    m_quads.clear();
}

void CubeRenderer::cleanUp() {
    m_Texture.cleanUp();
    grass_model.deleteData();
    ground_model.deleteData();
    m_shader.cleanUp();
}

