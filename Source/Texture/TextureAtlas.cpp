#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& textureFileName):BasicTexture(textureFileName)
{
    m_imageSize             = 256;
    m_individualTextureSize = 16;
}

std::vector<GLfloat> TextureAtlas::getTexture(const std::string name) {
    auto top    = getTextureCoords({0, 0});
    auto side   = getTextureCoords({1, 0});
    auto bottom = getTextureCoords({2, 0});
    std::vector<GLfloat> texCoords;
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), top.begin(),      top.end());
    texCoords.insert(texCoords.end(), bottom.begin(),   bottom.end());
    return texCoords;
}

std::vector<GLfloat> TextureAtlas::getTextureCoords(const glm::vec2& coords)
{
    static const GLfloat TEX_PER_ROW      = (GLfloat)m_imageSize / (GLfloat)m_individualTextureSize;
    static const GLfloat INDV_TEX_SIZE    = 1.0f / TEX_PER_ROW;
    // bottom left is the origin (0, 0).
    // so use an offset to access to top left pixels.
    auto offset = 1 - INDV_TEX_SIZE;
    auto xMin = (coords.x * INDV_TEX_SIZE);
    auto yMin = (coords.y * INDV_TEX_SIZE) + offset;
    auto xMax = (xMin + INDV_TEX_SIZE);
    auto yMax = yMin+INDV_TEX_SIZE;

    // front texture coords should be : 0 0.9375, 0.0625 0.9375, 0.0625 1, 0 1
    return
    {
        // order according to counter clock-wise vertex arrangement.
        xMin, yMin,
        xMax, yMin,
        xMax, yMax,
        xMin, yMax,
    };
}
