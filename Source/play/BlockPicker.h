//
// Created by koncle on 2019/6/14.
//

#ifndef OPENGLPROJECTS_MOUSEPICKER_H
#define OPENGLPROJECTS_MOUSEPICKER_H

#include "utils.cpp"
#include "glmlib.h"
#include "../World/World.h"
#include "Player.h"
#include "math.h"


class BlockPicker{
private:
    glm::vec3 ray=glm::vec3(0.);
    int MAX_STEP = 100;
    Player &player;

public:
    BlockPicker(Player &player):player(player){}

    glm::vec3 getAroundBlock(GLFWwindow* window, World& world){
        updateRay(window);
        glm::vec3 targetBlock = stepRay(world);
        if(targetBlock.x == -1)
            return targetBlock;
        else
            return getBlockAroundTarget(player.position, targetBlock);
    }

    glm::vec3 getDirectBlock(GLFWwindow* window, World& world){
        updateRay(window);
        glm::vec3 targetBlock = stepRay(world);
        return targetBlock;
    }

    bool pos_in_square(float pos_x, float pos_y, float rec_top_left_x, float rec_top_left_y,
                       float rec_bottom_right_x, float rec_bottom_right_y){
        std::cout << "(" << pos_x << ", " << pos_y << ")" << std::endl;
        bool res = pos_x >= rec_top_left_x && pos_x <= rec_bottom_right_x && pos_y >= rec_bottom_right_y && pos_y <= rec_top_left_y;
        std::cout << "(" << rec_top_left_x << ", " <<  rec_top_left_y << ", " << rec_bottom_right_x << ", " << rec_bottom_right_y << ")" << std::endl;
        return res;
    }

    glm::vec3 intersec_with_block(glm::vec3 myPos, glm::vec3 blockPos, glm::vec3 targetPos){
        auto dir = targetPos - myPos ;

        std::cout << "Block pos" << "(" << blockPos.x << ", " << blockPos.y << ", " << blockPos.z << ")" << std::endl;
        auto scale_factor = (blockPos -myPos)/ dir;
        auto scale_factor_2 = (blockPos + 1.f - myPos) / dir;
        // test left plane, scale z
        if(dir.x > 0){
            auto z_scaled =  myPos + dir * scale_factor.x;
            std::cout << "(" << z_scaled.x << ", " << z_scaled.y << ", " << z_scaled.z << ")" << std::endl;
            if (pos_in_square(z_scaled.z, z_scaled.y, blockPos.z, blockPos.y+1., blockPos.z+1, blockPos.y)) return glm::vec3(-1, 0, 0);
        }
        if(dir.x <= 0){
            auto z_scaled = myPos + dir * scale_factor_2.x;
            std::cout << "(" << z_scaled.x << ", " << z_scaled.y << ", " << z_scaled.z << ")" << std::endl;
            if (pos_in_square(z_scaled.z, z_scaled.y, blockPos.z, blockPos.y+1., blockPos.z+1, blockPos.y)) return glm::vec3(1, 0, 0);
        }

        if(dir.y > 0){
            auto z_scaled = myPos + dir * scale_factor.y;
            std::cout << "(" << z_scaled.x << ", " << z_scaled.y << ", " << z_scaled.z << ")" << std::endl;
            if (pos_in_square(z_scaled.x, z_scaled.z, blockPos.x, blockPos.z+1., blockPos.x+1, blockPos.z)) return glm::vec3(0, -1, 0);
        }
        if(dir.y <= 0){
            auto z_scaled = myPos + dir * scale_factor_2.y;
            std::cout << "(" << z_scaled.x << ", " << z_scaled.y << ", " << z_scaled.z << ")" << std::endl;
            if (pos_in_square(z_scaled.x, z_scaled.z, blockPos.x, blockPos.z+1., blockPos.x+1, blockPos.z)) return glm::vec3(0, 1, 0);
        }

        if(dir.z > 0){
            auto z_scaled = myPos + dir * scale_factor.z;
            std::cout << "(" << z_scaled.x << ", " << z_scaled.y << ", " << z_scaled.z << ")" << std::endl;
            if (pos_in_square(z_scaled.x, z_scaled.y, blockPos.x, blockPos.y+1., blockPos.x+1, blockPos.y)) return glm::vec3(0, 0, -1);
        }
        if(dir.z <= 0){
            auto z_scaled = myPos + dir * scale_factor_2.z;
            std::cout << "(" << z_scaled.x << ", " << z_scaled.y << ", " << z_scaled.z << ")" << std::endl;
            if (pos_in_square(z_scaled.x, z_scaled.y, blockPos.x, blockPos.y+1., blockPos.x+1, blockPos.y)) return glm::vec3(0, 0, 1);
        }
        return glm::vec3(0, 0, 0);
    }

    glm::vec3 getBlockAroundTarget(glm::vec3 yourPos, glm::vec3 targetPos){
//        targetPos += 0.5;
        auto x = int(targetPos.x);
        auto y = int(targetPos.y);
        auto z = int(targetPos.z);
        std::cout << "Your Pos (" << yourPos.x << ", " <<  yourPos.y << ", " << yourPos.z << ")!!" << std::endl;
        std::cout << "target Pos (" << targetPos.x << ", " <<  targetPos.y << ", " <<  targetPos.z << ")!!" << std::endl;
        auto change = intersec_with_block(yourPos, glm::vec3(x, y, z), targetPos);
        std::cout << "Final (" << targetPos.x << ", " <<  targetPos.y << ", " <<  targetPos.z << ")!!" << std::endl<< std::endl;
        return targetPos+change;
    }

    glm::vec3 stepRay(World& world){
        auto position = player.position ;
        for (int step = 0; step < MAX_STEP; ++step) {
            auto target_position = position + float(step) * ray;
            auto entity = world.getEntity(target_position.x, target_position.y ,target_position.z);
            if (entity.type != AIR){
                return target_position;
            }
        }
        // std::cout << "nothing in front of you!" << std::endl;
        return glm::vec3(-1, -1, -1);
    }

    void updateRay(GLFWwindow* window)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float x = 0.f;
        float y = 0.f;
        glm::vec4 clipCoords = glm::vec4(0.f, 0.f, -1.f, 1.f);

        auto proj = player.getProjectionMatrix();
        auto invProj = glm::inverse(proj);
        glm::vec4 eyeCoords = invProj*clipCoords;
        eyeCoords.z = -1.f; eyeCoords.w = 0.f;

        auto view = player.getViewMatrix();
        auto invView = glm::inverse(view);
        glm::vec4 worldCoords = invView*eyeCoords;
        glm::vec4 mouseRay = glm::normalize(worldCoords);
        ray = glm::vec3(mouseRay.x, mouseRay.y, mouseRay.z);
    }
};
#endif //OPENGLPROJECTS_MOUSEPICKER_H
