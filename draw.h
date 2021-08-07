//
// Created by darc on 2021/8/7.
//

#ifndef OPENGL_STARTER_DRAW_H
#define OPENGL_STARTER_DRAW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Draw {
public:
    Draw();
    void initBuffer();
    void initPipe();
    void drawCall() const;

private:
    const float vertices[12]{
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };
    const unsigned int indices[6]{
        0, 1, 3, // 上半个三角形
        1, 2, 3, // 下半个三角形
    };
    unsigned int vbo, vao, ibo;
    unsigned int vertexShader, fragmentShader;
    unsigned int shaderProgram;
    const char *vertexShaderSource = "#version 460 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main() {\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}";
    const char *fragmentShaderSource = "#version 460 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main() {\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n";
};


#endif //OPENGL_STARTER_DRAW_H
