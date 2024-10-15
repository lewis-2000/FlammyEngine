#include "camera.h"  
#include "input.h"
#include <iostream>
#include <glm/glm.hpp> // For possible camera or movement logic

// Initialize static members
std::map<int, bool> Input::keys;
float Input::movementSpeed = 2.5f;
float Input::cameraSpeed = 2.5f;

void Input::initialize(GLFWwindow* window) {
    // Set the key callback to handle key press events
    glfwSetKeyCallback(window, keyCallback);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Check for key press or release and store the state
    if (action == GLFW_PRESS) {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

bool Input::isKeyPressed(int key) {
    // Return true if the key is pressed, false otherwise
    return keys[key];
}

void Input::processKeyInput(GLFWwindow* window, float deltaTime) {
    // Use key states to move the camera or other objects
    if (isKeyPressed(GLFW_KEY_W)) {
        moveForward(deltaTime);
    }
    if (isKeyPressed(GLFW_KEY_S)) {
        moveBackward(deltaTime);
    }
    if (isKeyPressed(GLFW_KEY_A)) {
        moveLeft(deltaTime);
    }
    if (isKeyPressed(GLFW_KEY_D)) {
        moveRight(deltaTime);
    }
}

void Input::moveForward(float deltaTime) {
    // Add logic to move the object or camera forward
    std::cout << "Moving forward" << std::endl;
}

void Input::moveBackward(float deltaTime) {
    // Add logic to move the object or camera backward
    std::cout << "Moving backward" << std::endl;
}

void Input::moveLeft(float deltaTime) {
    // Add logic to move the object or camera left
    std::cout << "Moving left" << std::endl;
}

void Input::moveRight(float deltaTime) {
    // Add logic to move the object or camera right
    std::cout << "Moving right" << std::endl;
}
