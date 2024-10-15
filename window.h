#pragma once

#include "camera.h"  // Include your Camera class here
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int height, int width);
    ~Window();
    void init();
    void run();
    void processInput(GLFWwindow* window);

    int getHeight() const { return winHeight; }
    int getWidth() const { return winWidth; }

    GLFWwindow* getNativeWindow() const { return window; }

private:
    int winHeight;
    int winWidth;
    GLFWwindow* window;

    Camera camera;  // Add camera object
    float deltaTime = 0.0f;  // Add deltaTime for smooth movement
    float lastFrame = 0.0f;  // Time of last frame
};
