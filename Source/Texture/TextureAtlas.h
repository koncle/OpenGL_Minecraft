#ifndef TEXTUREATLAS_H_INCLUDED
#define TEXTUREATLAS_H_INCLUDED

#include "BasicTexture.h"
#include <vector>
#include "../World/Constants.h"

class TextureAtlas : public BasicTexture
{
    public:
        TextureAtlas(const std::string& textureFileName);

        std::vector<GLfloat> getTexture(const int type);
        std::vector<GLfloat> getTextureCoords(const glm::vec2& coords);

    private:
        int m_imageSize;
        int m_individualTextureSize;
};

#endif // TEXTUREATLAS_H_INCLUDED
