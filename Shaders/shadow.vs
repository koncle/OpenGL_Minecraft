#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 Model;
uniform mat4 ProjView;

uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = ProjView * lightSpaceMatrix * Model * vec4(aPos, 1.0);
}