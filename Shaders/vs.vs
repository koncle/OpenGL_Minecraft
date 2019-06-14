#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 Model;
uniform mat4 ProjView;

uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = ProjView * Model * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}