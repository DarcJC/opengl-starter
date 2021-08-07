//
// Created by darc on 2021/8/7.
//

#include "draw.h"

void Draw::drawCall() const {
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Draw::initBuffer() {
    // 创建一个大小为1的顶点数组对象 并绑定到OpenGL
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // 创建一个大小为1的索引缓冲对象 并绑定到OpenGL
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // 创建一个大小为1的顶点缓冲对象 并绑定到OpenGL
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 复制顶点和索引到缓冲区中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 设置缓冲区
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
}

void Draw::initPipe() {
    // 编译顶点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // 编译片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // 着色器链接
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    // 清理编译的着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Draw::Draw() {
    initBuffer();
    initPipe();
}
