//
// Created by koncle on 2019/6/13.
//

#include "GUIRenderer.h"

GUIRenderer::GUIRenderer() : m_shader("gui.vs", "gui.fs"){
    m_model.addData({
                 1,   1, 0,
                 -1,  1, 0,
                 -1, -1, 0,
                 1,  -1, 0},
                         {1, 1,
                          0, 1,
                          0, 0,
                          1, 0},
                {0, 1, 2,
                 2, 3, 0});
}

void GUIRenderer::add(GUIEntity& guiEntity) {
    m_guiEntities.push_back(guiEntity);
}

void GUIRenderer::render() {
    m_shader.use();
    m_model.bindVAO();

    for(int i = 0; i < m_guiEntities.size(); ++i){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_guiEntities[i].texture_id);
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, m_guiEntities[i].position);
        model = glm::scale(model, m_guiEntities[i].scale);
        m_shader.setMat4("transform", model);
        glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }
    m_model.unbindVAO();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GUIRenderer::cleanUp() {

}
