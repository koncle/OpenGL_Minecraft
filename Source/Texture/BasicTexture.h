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
    BasicTexture(const std::string& file)
    {
        loadFromFile(file);
    }
    std::vector<GLfloat> getTexture(const std::string name) {
        return  {
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,
                0.0f, 1.0f,

                0.0f, 0.1f,
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,

                1.0f, 0.0f,
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,

                1.0f, 0.0f,
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
//
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,
//
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,};
    }

    void bindTexture() const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    GLuint getTextureId() {
        return m_id;
    }

    void loadFromData(const int width, const int height, const unsigned char *data)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint loadFromFile(const std::string& file)
    {
        // 加载纹理图片
        int width, height, nrChannels;

        std::string f = "../Res/Textures/" + file;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(f.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            // 对当前纹理对象，使用多级渐远纹理
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
            throw std::runtime_error("Failed to load texture");
        }
        loadFromData(width, height, data);
        stbi_image_free(data);
        return m_id;
    }

};
#endif //OPENGLPROJECTS_A_H
