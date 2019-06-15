#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNorm;

out vec2 TexCoord;
out vec4 shadowCoords;
// for light
out vec3 FragPos;
out vec3 Normal;

uniform mat4 Model;
uniform mat4 ProjView;

uniform mat4 shadowMapSpace;

void main()
{
    gl_Position = ProjView * Model * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);

    vec4 a = shadowMapSpace * Model * vec4(aPos, 1.0);
    float y = 1.0 - a.y;
    shadowCoords = vec4(a.x, y, a.z, a.w);

    Normal = aNorm;
    FragPos = vec3(Model * vec4(aPos, 1.0f));
}