#include "shader.h"
#include "opengl_renderer.h"
#include "scene_manager.h"
#include "shape_node.h"
#include "window.h"
#include "input.h"

int main() {
    // Initialize window and OpenGL context
    Window myWindow(800, 800);
    myWindow.init();

    // Initialize OpenGL renderer
    OpenGLRenderer renderer(myWindow.getNativeWindow());
    renderer.init();

    // Load the shader program
    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // Create the scene manager
    SceneManager sceneManager;

    // Create the root node of the scene
    auto rootNode = std::make_shared<SceneNode>();

    // Create a shape node (e.g., a square)
    auto shapeNode = std::make_shared<ShapeNode>(shader);
    rootNode->addChild(shapeNode);  // Add the shape to the scene

    // Set the root node in the scene manager
    sceneManager.setRoot(rootNode);

    // Main rendering loop
    while (!glfwWindowShouldClose(myWindow.getNativeWindow())) {
        renderer.clear();

        sceneManager.update();  // Update scene (animations, etc.)
        sceneManager.render();  // Render scene

        renderer.swapBuffers();  // Present the frame
        glfwPollEvents();        // Handle window events
    }

    return 0;
}