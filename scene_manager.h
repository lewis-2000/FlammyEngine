#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene_node.h"
#include <memory>
#include <unordered_map>

class SceneManager {
public:
    // Constructor
    SceneManager();

    // Set the root of the scene graph
    void setRoot(std::shared_ptr<SceneNode> rootNode);

    // Switch to a new scene based on scene ID
    void switchScene(int sceneId, std::shared_ptr<SceneNode> newSceneRoot);

    // Update the entire scene (e.g., animations, logic)
    void update();

    // Render the entire scene
    void render();

    std::unordered_map<int, std::shared_ptr<SceneNode>> sceneCache; // Caches scenes by ID for reuse
private:
    std::shared_ptr<SceneNode> root; // Root node of the scene graph
    int activeSceneId; // Keeps track of the currently active scene
};

#endif // SCENE_MANAGER_H
