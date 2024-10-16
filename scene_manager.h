#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene_node.h"
#include <memory>

class SceneManager {
public:
    // Constructor
    SceneManager();

    // Set the root of the scene graph
    void setRoot(std::shared_ptr<SceneNode> rootNode);

    // Switch to a new scene
    void switchScene(std::shared_ptr<SceneNode> newSceneRoot);

    // Update the entire scene (e.g., animations, logic)
    void update();

    // Render the entire scene
    void render();

private:
    std::shared_ptr<SceneNode> root; // Root node of the scene graph
};

#endif // !SCENE_MANAGER_H
