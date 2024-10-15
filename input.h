#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <map>

class Input {
public:
    // Store key states (pressed or released)
    static std::map<int, bool> keys;

    // Initialize the input system (register callbacks, etc.)
    static void initialize(GLFWwindow* window);

    // Process key input events (will be called per frame to check key states)
    static void processKeyInput(GLFWwindow* window, float deltaTime);

    // GLFW key callback function
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // Check if a key is pressed
    static bool isKeyPressed(int key);

private:
    // Private constructor to prevent instantiation (static class)
    Input() {}

    // Private key states for tracking
    static float movementSpeed;
    static float cameraSpeed;

    // Helper methods for key actions
    static void moveForward(float deltaTime);
    static void moveBackward(float deltaTime);
    static void moveLeft(float deltaTime);
    static void moveRight(float deltaTime);
};

#endif
