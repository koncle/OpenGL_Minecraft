#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>
#include "glad/glad.h"
#include "glmlib.h"
#include <GLFW/glfw3.h>
#include "../NonCopyable.h"
#include "stb_image/stb_image.h"

class Texture
{
    public:
        Texture() = default;
        Texture(const std::string& file);

        ~Texture();

        void loadFromFile (const std::string& file);

        void bindTexture() const;


    private:
        GLuint m_id;
};

#endif // TEXTURE_H_INCLUDED
