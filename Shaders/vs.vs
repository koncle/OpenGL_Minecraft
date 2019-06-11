#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

// transform matrix
uniform mat4 transform;

uniform mat4 Model;
uniform mat4 ProjView;

void main()
{
    gl_Position = ProjView * Model * vec4(aPos, 1.0);
    // gl_Position =  vec4(aPos, 1.0);
    // TexCoord = aTexCoord;
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}