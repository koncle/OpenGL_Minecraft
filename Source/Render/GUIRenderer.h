//
// Created by koncle on 2019/6/13.
//

#ifndef OPENGLPROJECTS_GUIRENDERER_H
#define OPENGLPROJECTS_GUIRENDERER_H

#include "../GUI/GUIEntity.h"
#include "../World/Model.h"

#include "../play/Player.h"
#include "../Shader/shader.h"

class Shader;

class GUIRenderer{
public:
    GUIRenderer();
    void add(GUIEntity &guiEntity);
    void render();
    void cleanUp();
    Shader m_shader;

private:
    std::vector<GUIEntity> m_guiEntities;
    Model m_model;
};
#endif //OPENGLPROJECTS_GUIRENDERER_H
