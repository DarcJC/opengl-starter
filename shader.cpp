//
// Created by darc on 2021/8/8.
//

#include "shader.h"
#include "stb_image.h"

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

Texture2D::Texture2D(const GLchar *path) {
    // 加载图片
    unsigned char* data = stbi_load(path, &originWidth, &originHeight, &nrChannels, 0);
    if (!data) {
        std::cout << "Failed to load texture from " << path << std::endl;
    } else {
        // 构造OpenGL纹理对象
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        // 设置纹理属性
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 设置纹理数据
        // 判断通道数，如果大于三就使用RGBA读取
        if (nrChannels > 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, originWidth, originHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, originWidth, originHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    // 释放加载的图片数据 并取消绑定
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::bindUnit(const GLenum texture) const {
    if (texture < GL_TEXTURE0 || texture > GL_TEXTURE31) throw "Invalid Unit";
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, id);
}
