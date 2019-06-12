//
// Created by koncle on 2019/6/11.
//
#include "Renderer.h"
#include "../Texture/TextureAtlas.h"

Renderer::Renderer(const char *img_path) : m_Texture(img_path) {

    std::vector<GLfloat> texCoords = m_Texture.getTexture("default");
//    int i = 0;
//    for (const auto &item : texCoords) {
//        std::cout << item << " ";
//        if(++i%8==0){
//            std:: cout << std::endl;
//        }
//    }
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

void Renderer::add(glm::vec3 &position) {
    m_quads.push_back(position);
}

void Renderer::render(Player &camera) {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.use();
    m_Texture.bindTexture();
    m_model.bindVAO();

    auto ProjViewMatrix = camera.getProjViewMatrix();
    m_shader.setMat4("ProjView", ProjViewMatrix);

    for (auto &quad : m_quads) {
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, quad);
//        float angle = 20.0f * (3 + 1);
//        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(angle), glm::vec3(1.f, 0.3f, .5f));
        m_shader.setMat4("Model", model);
        glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }

    m_quads.clear();

}

