//
// Created by darc on 2021/8/7.
//

#include "draw.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Draw::drawCall() const {
    // 设置使用的着色器
    shaderProgram.use();
    auto now = (float)glfwGetTime();
    // 打开深度缓冲
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    // 清除颜色缓冲区以设置背景颜色
    auto redValue = std::sin(now) / 2.0f + 0.5f;
    glClearColor(redValue, .0f, .0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // 设置各个空间的转换矩阵
    glm::mat4 model(1.0f); // 世界空间绕着为局部空间绕x轴旋转-55度
    model = glm::rotate(model, now * glm::radians(50.0f), glm::vec3(.5f, 1.0f, .0f));
    glm::mat4 view(1.0f); // 观察空间为原点“后退”3步
    view = glm::translate(view, glm::vec3(.0f, .0f, -3.0f));
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, .1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // 绑定OpenGL对象并渲染
    texture.bindUnit(GL_TEXTURE0);
    texture1.bindUnit(GL_TEXTURE1);
    shaderProgram.setInt("customTexture", 0);
    shaderProgram.setInt("texture1", 1);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 40);
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr); // 位置属性
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // 取消绑定VAO
    glBindVertexArray(0);
}

Draw::Draw(int width, int height)
: shaderProgram("shaders/simple.vert.glsl", "shaders/simple.frag.glsl"),
  texture("textures/container.jpg"),
  texture1("textures/awesomeface.png"),
  width(width), height(height){
    initBuffer();
}
