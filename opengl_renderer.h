#pragma once
#include "renderer.h"
#include <glad/glad.h>  //  GLAD for loading OpenGL functions
#include <GLFW/glfw3.h>

class OpenGLRenderer : public Renderer {
public:
    OpenGLRenderer(GLFWwindow* window) : window(window) {}

    void init() override;
    void clear() override;
    void draw() override;
    void swapBuffers() override;

private:
    GLFWwindow* window; // GLFW window pointer for buffer swapping
};
