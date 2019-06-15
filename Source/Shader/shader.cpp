//
// Created by koncle on 2019/3/17.
//

#include <glmlib.h>
#include "shader.h"

void checkShaderCompileStatus(unsigned int shader){
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
    }
    assert(success);
}

void checkShaderProgramStatus(unsigned int program) {
    int  success;
    char infoLog[512];
    glGetShaderiv(program, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw std::runtime_error("ERROR::SHADER::VERTEX::PROGRAM_FAILED");
    }
    assert(success);
}

unsigned int getShader(GLenum CODE, const char* src){
    unsigned shader = glCreateShader(CODE);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    // 打印编译错误（如果有的话）
    checkShaderCompileStatus(shader);
    return shader;
}


Shader::Shader(const std::string& vertexP, const std::string& fragmentP) {
    auto vertexPath = "../Shaders/"+vertexP;
    auto fragmentPath = "../Shaders/"+fragmentP;
    // 1. 从文件路径中获取顶点/片段着色器
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << " " << vertexPath << std::endl;
        throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // 顶点着色器

    unsigned int vertex = getShader(GL_VERTEX_SHADER, vShaderCode);
    std::cout << "complete vertex shader!" << vertexP << std::endl;
    // 片段着色器
    unsigned int fragment = getShader(GL_FRAGMENT_SHADER, fShaderCode);
    std::cout << "complete fragment shader!" << fragmentP << std::endl;

    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // 打印连接错误（如果有的话）
    checkShaderProgramStatus(ID);

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    std::cout<< vertexP << " my id : " << ID << std::endl;

}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::set(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::set(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set(const std::string &name, float v1, float v2, float v3, float v4) const
{
    int p = glGetUniformLocation(ID, name.c_str());
    assert(p != -1);
    glUniform4f(p, v1, v2, v3, v4);
}

void Shader::set(const std::string &name, float v1, float v2, float v3) const {
    int loc = glGetUniformLocation(ID, name.c_str());
    assert(loc != -1);
    glUniform3f(loc, v1, v2, v3);
}

void Shader::setVec3(const std::string &name, glm::vec3 vec3) const {
    int loc = glGetUniformLocation(ID, name.c_str());
    assert(loc != -1);
    glUniform3f(loc, vec3.x, vec3.y, vec3.z);
}

void Shader::setMat4(const std::string &name, glm::mat4 mat) {
    GLint loc = glGetUniformLocation(ID, name.c_str());
    assert(loc != -1);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::cleanUp() {
    glDeleteProgram(ID);
}
