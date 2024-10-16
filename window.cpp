#include "window.h"
#include "shader.h"
#include "scene_manager.h"
#include "shape_node.h"
#include "Scene2.h"
#include "opengl_renderer.h"
#include <iostream>

// Create scene manager
SceneManager sceneManager;


//// Create the root node of the scene
//auto rootNode = std::make_shared<SceneNode>();

// Handle Scene Switching
void handleInput(GLFWwindow* window, Shader& shaderScene1, Shader& shaderScene2) {
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        // Create and set scene 1
        auto scene1 = std::make_shared<ShapeNode>(shaderScene1);
        sceneManager.switchScene(scene1);
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        // Create and set scene 2
        auto scene2 = std::make_shared<Scene2>(shaderScene2);
        sceneManager.switchScene(scene2);
    }
    // Add more scenes for other keys (3, 4, etc.) if needed
}





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
        std::cout << "LOG - Failed to initialize GLFW" << std::endl;
        return;
    }

    window = glfwCreateWindow(winWidth, winHeight, "Flammy Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "LOG - Failed to create window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Enable V-Sync
    //glfwSwapInterval(1);


    std::cout << "LOG - WINDOW RUNNING" << std::endl;

    // Set input mode to capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "LOG - Failed to initialize GLAD" << std::endl;
        return;
    }
}

// Main loop
void Window::run() {
    // Initialize the OpenGL renderer
    OpenGLRenderer renderer(window);
    renderer.init();  // Initialize the renderer (OpenGL context)

    // Load shaders
    Shader shaderScene1("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Shader shaderScene2("shaders/secondSceneVertex_shader.glsl", "shaders/secondSceneFragment_shader.glsl");


    // Create initial scene
    auto initialScene = std::make_shared<ShapeNode>(shaderScene1);
    sceneManager.setRoot(initialScene);

    // Game loop
    while (!glfwWindowShouldClose(window)) {

        // Clear the screen using the renderer
        renderer.clear();

        handleInput(window, shaderScene1, shaderScene2);

        // Update and render the scene
        sceneManager.update();
        sceneManager.render();

        // Swap buffers (renderer handles this)
        renderer.swapBuffers();

        // Poll window events
        glfwPollEvents();
    }
}
