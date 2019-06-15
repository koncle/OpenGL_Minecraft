//
// Created by koncle on 2019/6/13.
//

#ifndef OPENGLPROJECTS_MASTERRENDERER_H
#define OPENGLPROJECTS_MASTERRENDERER_H

#include "glhead.h"
#include "../play/Player.h"
#include "../World/World.h"
#include "CubeRenderer.h"
#include "GUIRenderer.h"
#include "../Shadow/Shadow.h"

class GUIRenderer;
class CubeRenderer;
class Player;

class MasterRenderer{
public:
    MasterRenderer();
    void renderCube(glm::vec3 &position);
    void renderWorld(World &world);
    void renderGUI(GUIEntity &guiEntity);
    void finishRender(Player &player, Shadow &shadow);
    void finishRenderShadow(Player &player, Shadow &shadow);
    void cleanUp();
private:
    GUIRenderer* guiRenderer;
    CubeRenderer* cubeRenderer;
};
#endif //OPENGLPROJECTS_MASTERRENDERER_H
