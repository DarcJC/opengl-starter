//
// Created by darc on 2021/8/8.
//

#include "shader.h"

ShaderProgram::ShaderProgram(const GLchar *vertexPath, const GLchar *fragmentPath) {
    using namespace std;
    // 初始化变量
    string vertexCode, fragmentCode;
    ifstream vertexFile, fragmentFile;
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // 尝试读取文件
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        stringstream vertexStream, fragmentStream;
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close(); fragmentFile.close();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    } catch (ifstream::failure& err) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
    }
    const char* cVertexCode = vertexCode.c_str();
    const char* cFragmentCode = fragmentCode.c_str();

    // 编译着色器
    unsigned int vertex, fragment;

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &cVertexCode, nullptr);
    glCompileShader(vertex);
    printCompileError(vertex);
    // 片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &cFragmentCode, nullptr);
    glCompileShader(fragment);
    printCompileError(fragment);

    // 链接着色器
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    printLinkError(id);

    // 删除着色器缓存
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void ShaderProgram::use() const {
    glUseProgram(id);
}

void ShaderProgram::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void printCompileError(unsigned int id) {
    int success;
    char err[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, nullptr, err);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << err << std::endl;
    }
}

void printLinkError(unsigned int id) {
    int success;
    char err[512];
    glGetProgramiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, err);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << err << std::endl;
    }
}
