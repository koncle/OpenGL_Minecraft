#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>
#include "glad/glad.h"
#include "glmlib.h"
#include <GLFW/glfw3.h>
#include "../Utils/NonCopyable.h"
#include "stb_image/stb_image.h"
#include <iostream>
#include <vector>

class BasicTexture : public NonCopyable
{
    public:
        BasicTexture() = default;
        BasicTexture(const std::string& file);

        ~BasicTexture();

        void loadFromData(const int width, const int height, const unsigned char *data);
        void loadFromFile (const std::string& file);

        void bindTexture() const;
        std::vector<GLfloat> getTexture(const std::string name);
    private:
        GLuint m_id;
};

#endif // TEXTURE_H_INCLUDED
