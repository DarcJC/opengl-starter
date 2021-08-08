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
    const float vertices[18]{
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };
    const unsigned int indices[6]{
        0, 1, 2,
    };
    unsigned int vbo, vao, ibo;
    unsigned int vertexShader, fragmentShader;
    unsigned int shaderProgram;
    const char *vertexShaderSource = "#version 460 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "out vec3 customColor;"
                                     "void main() {\n"
                                     "    gl_Position = vec4(aPos, 1.0);\n"
                                     "    customColor = aColor;"
                                     "}";
    const char *fragmentShaderSource = "#version 460 core\n"
                                       "out vec4 fragColor;\n"
                                       "in vec3 customColor;"
                                       "void main() {\n"
                                       "    fragColor = vec4(customColor, 1.0);\n"
                                       "}\n";
};


#endif //OPENGL_STARTER_DRAW_H
