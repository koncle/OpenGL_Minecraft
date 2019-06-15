//
// Created by koncle on 2019/6/14.
//

#ifndef OPENGLPROJECTS_A_H
#define OPENGLPROJECTS_A_H

#include <glhead.h>
#include <stb_image/stb_image.h>

class BasicTexture{
public:
    unsigned int m_id;
    BasicTexture(const std::string& file);
    std::vector<GLfloat> getTexture(const int type);
    void bindTexture() const;
    GLuint getTextureId();
    void cleanUp();

    void loadFromData(const int width, const int height, const unsigned char *data);
    GLuint loadFromFile(const std::string& file);
};
#endif //OPENGLPROJECTS_A_H
