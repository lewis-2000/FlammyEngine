#include "scene_manager.h"
#include <glm/gtc/matrix_transform.hpp> // For transformations

// Constructor
SceneManager::SceneManager() : root(nullptr) {}

// Set the root of the scene graph
void SceneManager::setRoot(std::shared_ptr<SceneNode> rootNode) {
    root = rootNode;
}

// Update the scene (this could be more advanced with animations, physics, etc.)
void SceneManager::update() {
    // Traverse the scene graph and update nodes if needed (e.g., animations)
}

// Render the scene by traversing the scene graph
void SceneManager::render() {
    if (root) {
        glm::mat4 identity = glm::mat4(1.0f); // Identity matrix as the root's parent
        root->render(identity); // Start rendering from the root node
    }
}
