//
// Created by koncle on 2019/6/13.
//

#include "MasterRenderer.h"
#include "../Texture/BasicTexture.h"

MasterRenderer::MasterRenderer(){
    cubeRenderer = new CubeRenderer("DefaultPack.png", "cube.vs", "cube.fs");
    guiRenderer = new GUIRenderer();
}

void MasterRenderer::renderCube(Entity &entity) {
    cubeRenderer->add(entity);
}

void MasterRenderer::renderGUI(GUIEntity &guientity) {
    guiRenderer->add(guientity);
}


void MasterRenderer::finishRender(Player &player, Shadow &shadow) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cubeRenderer->render(player, shadow);
    guiRenderer->render();
}

void MasterRenderer::finishRenderShadow(Player &player, Shadow& shadow) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cubeRenderer->renderShadow(player, shadow);
}

void MasterRenderer::cleanUp() {
    cubeRenderer->cleanUp();
    guiRenderer->cleanUp();
    delete cubeRenderer;
    delete guiRenderer;
}

void MasterRenderer::renderWorld(World &world) {
    // render objects
    std::vector<Entity>** map = world.getWorldMap();
    for(uint i = 0; i < MAX_WIDTH; ++i){
        for(uint j = 0; j < MAX_WIDTH; ++j){
            auto vector = map[i][j];
            for(auto &entity :vector ){
                if(entity.position.y >= MIN_LEVEL) {
                    renderCube(entity);
                }
            }
        }
    }
}

