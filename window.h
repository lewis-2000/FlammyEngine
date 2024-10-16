#ifndef WINDOW
#define WINDOW

#include "camera.h"  // Include your Camera class here
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int height, int width);
    ~Window();
    void init();
    void run();

    int getHeight() const { return winHeight; }
    int getWidth() const { return winWidth; }

    GLFWwindow* getNativeWindow() const { return window; }


private:
    int winHeight;
    int winWidth;
    GLFWwindow* window;

    Camera camera;  // Add camera object
};

#endif