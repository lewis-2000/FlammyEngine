#ifndef SCENE_NODE_H
#define SCENE_NODE_H



#include <glm/glm.hpp>  // For math and matrix operations
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

class SceneNode {
public:
    // Constructor
    SceneNode();

    // Add a child node
    void addChild(std::shared_ptr<SceneNode> child);

    // Set the transformation (e.g., position)
    void setTransformation(const glm::mat4& transform);

    // Get the transformation of this node
    glm::mat4 getTransformation() const;

    // Traverse and render the scene graph (recursive)
    virtual void render(const glm::mat4& parentTransform);

protected:
    glm::mat4 transformation; // Local transformation matrix

    std::vector<std::shared_ptr<SceneNode>> children; // Child nodes
};

#endif // !SCENE_NODE_H