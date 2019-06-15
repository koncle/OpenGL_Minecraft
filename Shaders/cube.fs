#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 shadowCoords;

in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    // shadow
    float objectNearestLight = texture(shadowMap, shadowCoords.xy).r;
    float lightFactor = 1.0;
    if(shadowCoords.z > objectNearestLight){
         lightFactor = 1.0 - 0.4;
    }

    // light
    vec4 objectColor = texture(texture1, TexCoord);

    // ambient
    float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // final color
    // FragColor = vec4((ambient + diffuse + specular), 1.0) * objectColor;
    FragColor = vec4((ambient + diffuse ), 1.0) * objectColor * lightFactor;
}