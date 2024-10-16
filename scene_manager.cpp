#include "scene_manager.h"
#include <glm/gtc/matrix_transform.hpp> // For transformations

// Constructor
SceneManager::SceneManager() : root(nullptr), activeSceneId(-1) {}

// Set the root of the scene graph
void SceneManager::setRoot(std::shared_ptr<SceneNode> rootNode) {
    root = rootNode;
}

// Switch to a new scene
void SceneManager::switchScene(int sceneId, std::shared_ptr<SceneNode> newRoot) {
    // Check if the scene is already active
    if (sceneId == activeSceneId) {
        return; // Do nothing if we are switching to the currently active scene
    }

    // Check if the scene is cached
    if (sceneCache.find(sceneId) != sceneCache.end()) {
        root = sceneCache[sceneId]; // Switch to cached scene
    }
    else {
        root = newRoot; // Set new scene as root
        sceneCache[sceneId] = newRoot; // Cache it for future use
    }

    activeSceneId = sceneId; // Update the currently active scene ID
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
