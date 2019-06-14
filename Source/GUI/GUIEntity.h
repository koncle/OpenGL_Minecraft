//
// Created by koncle on 2019/6/13.
//

#ifndef OPENGLPROJECTS_GUITEXTURE_H
#define OPENGLPROJECTS_GUITEXTURE_H

#include <glhead.h>
#include <vector>
#include "../Texture/BasicTexture.h"

class GUIEntity{
public:
    GUIEntity()= default;
    GUIEntity(const std::string &path,const std::vector<GLfloat>& position, const std::vector<GLfloat>& scale){
        BasicTexture texture(path);
        texture_id = texture.getTextureId();
        this->position.x = position[0];
        this->position.y = position[1];
        this->position.z = 0;
        this->scale.x = scale[0];
        this->scale.y = scale[1];
        this->scale.z = 0;
    }
    GUIEntity(GLuint texture_id, glm::vec3 position, glm::vec3 scale):
    texture_id(texture_id), position(position), scale(scale){}

    GLuint texture_id;
    glm::vec3 position;
    glm::vec3 scale;
};
#endif //OPENGLPROJECTS_GUITEXTURE_H
