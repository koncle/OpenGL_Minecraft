//
// Created by koncle on 2019/3/17.
//
#ifndef SHADER_H
#define SHADER_H
#include <glhead.h>
#include <fstream>
#include <sstream>
#include "assert.h"

class Shader{
public:
    unsigned int ID;
    Shader(): Shader("cube.vs", "cube.fs"){}
    Shader(const std::string& vertexP, const std::string& fragmentP);
    void cleanUp();
    void use();
    void set(const std::string &name, bool value) const;
    void set(const std::string &name, int value) const;
    void set(const std::string &name, float value) const;
    void set(const std::string &name, float v1, float v2, float v3) const;
    void set(const std::string &name, float v1, float v2, float v3, float v4) const;
    void setVec3(const std::string &name, glm::vec3 vec3) const;
    void setMat4(const std::string &name, glm::mat4 mat);
};

void checkShaderCompileStatus(unsigned int shader);

void checkShaderProgramStatus(unsigned int program);

unsigned int getShader(GLenum CODE, const char* src);
#endif

