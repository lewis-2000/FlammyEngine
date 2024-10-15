#include "opengl_renderer.h"
#include <iostream>

void OpenGLRenderer::init() {
    // Initialize GLAD before using any OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return;
    }

    // Enable depth testing (optional)
    glEnable(GL_DEPTH_TEST);
    std::cout << "LOG - OpenGL Renderer initialized using GLAD!" << std::endl;
}

void OpenGLRenderer::clear() {

    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::draw() {
    // OpenGL draw commands (this is where rendering logic goes)
}

void OpenGLRenderer::swapBuffers() {
    // Swap the buffers to present the rendered frame
    glfwSwapBuffers(window);
}
