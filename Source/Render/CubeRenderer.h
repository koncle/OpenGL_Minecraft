//
// Created by koncle on 2019/6/11.
//

#ifndef OPENGLPROJECTS_RENDERER_H
#define OPENGLPROJECTS_RENDERER_H

#include "glhead.h"
#include "../Shader/shader.h"
#include "../World/Model.h"
#include "../play/Player.h"
#include "../Texture/TextureAtlas.h"
#include "../Shadow/Shadow.h"

class Player;
class Shader;

class CubeRenderer{
public:
    CubeRenderer(const char* img_path, const char* vs, const char* fs);
    ~CubeRenderer(){cleanUp();};
    void add(Entity &entity);
    void render(Player& player, Shadow &shadow);
    void renderShadow(Player& player, Shadow& shadow);
    void cleanUp();
    Model grass_model;
    Model ground_model;
    Shader m_shader;
    TextureAtlas m_Texture;

private:
    std::vector<Entity> m_quads;
};
#endif //OPENGLPROJECTS_RENDERER_H
