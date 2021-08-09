//
// Created by darc on 2021/8/7.
//

#ifndef OPENGL_STARTER_DRAW_H
#define OPENGL_STARTER_DRAW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

class Draw {
public:
    Draw();
    void initBuffer();
    void drawCall() const;

private:
    const float vertices[32]{
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    const unsigned int indices[6]{
        0, 1, 3,
        1, 2, 3,
    };
    unsigned int vbo, vao, ibo;
    ShaderProgram shaderProgram;
    Texture2D texture;
};


#endif //OPENGL_STARTER_DRAW_H
