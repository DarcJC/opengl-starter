//
// Created by darc on 2021/8/8.
//

#ifndef OPENGL_STARTER_SHADER_H
#define OPENGL_STARTER_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void printCompileError(unsigned int id);
void printLinkError(unsigned int id);

class ShaderProgram {
public:
    unsigned int id; // 着色器程序ID

    ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
    // 使用/激活程序
    void use() const;
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

};


class Texture2D {
public:
    unsigned int id;
    int originWidth, originHeight, nrChannels; // 加载的图像属性

    explicit Texture2D(const GLchar* path);
    void bind() const;
};

#endif //OPENGL_STARTER_SHADER_H
