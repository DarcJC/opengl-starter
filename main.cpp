#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "draw.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Draw* drawInstance = nullptr;

int main() {

    // 关闭与stdio同步
    std::ios::sync_with_stdio(false);

    // 初始化GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL-Stater by Darc", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 初始化GLAD, 检查其是否正常工作
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    // 初始化视口（Viewport）
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 设置stb_image库
    stbi_set_flip_vertically_on_load(true);

    Draw draw(800, 600);
    drawInstance = &draw;
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框模式 用于调试
    // 进入渲染循环, 直到窗口被关闭
    while(!glfwWindowShouldClose(window)) {
        draw.drawCall();
        // 检查并调用事件 交换缓冲区
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理并退出
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    if (drawInstance) {
        drawInstance->width = width;
        drawInstance->height = height;
    }
}
