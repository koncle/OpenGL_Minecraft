//
// Created by koncle on 2019/6/11.
//

#ifndef OPENGLPROJECTS_RENDERER_H
#define OPENGLPROJECTS_RENDERER_H

#include <shader.h>
#include "../Model.h"
#include "glmlib.h"
#include "../Texture/texture.h"
#include "../Player/Player.h"

class Renderer{
public:
    Renderer(const char*img_path);
    void add(glm::vec3& position);
    void render(Player& player);

    Model m_model;
    Shader m_shader;
    Texture m_texture;

private:
    std::vector<glm::vec3> m_quads;
};
#endif //OPENGLPROJECTS_RENDERER_H
