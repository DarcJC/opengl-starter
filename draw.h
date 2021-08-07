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
    void drawCall();

private:
    const float vertices[9]{
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    unsigned int vbo, vao;
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
