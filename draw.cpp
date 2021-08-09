//
// Created by darc on 2021/8/7.
//

#include "draw.h"
#include <cmath>

void Draw::drawCall() const {
    // 设置使用的着色器
    shaderProgram.use();
    auto now = (float)glfwGetTime();
    // 清除颜色缓冲区以设置背景颜色
    auto redValue = std::sin(now) / 2.0f + 0.5f;
    glClearColor(redValue, .0f, .0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // 设置位置偏移
    auto offsetLocation = glGetUniformLocation(shaderProgram.id, "offset");
    glUniform3f(offsetLocation, .0f, redValue, .0f);
    // 绑定OpenGL对象并渲染
    texture.bindUnit(GL_TEXTURE0);
    texture1.bindUnit(GL_TEXTURE1);
    shaderProgram.setInt("customTexture", 0);
    shaderProgram.setInt("texture1", 1);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0); // 重置VAO 以免被其他渲染操作污染
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
    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr); // 位置属性
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // 颜色属性
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // 纹理坐标
    glEnableVertexAttribArray(2);
    // 取消绑定VAO
    glBindVertexArray(0);
}

Draw::Draw()
: shaderProgram("shaders/simple.vert.glsl", "shaders/simple.frag.glsl"),
  texture("textures/container.jpg"),
  texture1("textures/awesomeface.png"){
    initBuffer();
}
