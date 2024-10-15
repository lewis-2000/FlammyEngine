#include "window.h"
#include <iostream>
#include "input.h"

// GLFW: Window size change callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Constructor
Window::Window(int height, int width)
    : winHeight(height), winWidth(width), window(nullptr), camera(glm::vec3(0.0f, 0.0f, 3.0f)) {
}

// Destructor
Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

// Initialize window
void Window::init() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window = glfwCreateWindow(winWidth, winHeight, "Flammy Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // Set input mode to capture mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set callbacks for mouse movement (if required)
    // glfwSetCursorPosCallback(window, mouse_callback);
}

// Handle input for moving the camera
void Window::processInput(GLFWwindow* window) {
    std::cout << "LOG - MOUNTED PROCESS INPUT HANDLER " << std::endl;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    std::cout << "forward" << std::endl;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // You can also add mouse input for looking around using glfwGetCursorPos()
}

// Main loop
void Window::run() {
    while (!glfwWindowShouldClose(window)) {
        // Calculate deltaTime for smooth movement
        std::cout << "LOG - WINDOW RUNNING" << std::endl;
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Rendering would happen here, implement later

        glfwSwapBuffers(window);

        glfwPollEvents();


    }
}