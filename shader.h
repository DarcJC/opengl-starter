//
// Created by darc on 2021/8/8.
//

#ifndef OPENGL_STARTER_SHADER_H
#define OPENGL_STARTER_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void setMat4(const std::string &name, glm::mat4& mat4) const;

};


class Texture2D {
public:
    unsigned int id;
    int originWidth, originHeight, nrChannels; // 加载的图像属性

    explicit Texture2D(const GLchar* path);
    void bind() const;
    void bindUnit(GLenum texture) const;
};

#endif //OPENGL_STARTER_SHADER_H
