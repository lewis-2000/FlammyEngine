#include "scene_node.h"

// Constructor: initialize transformation to identity matrix
SceneNode::SceneNode() : transformation(glm::mat4(1.0f)) {}

// Add a child node to this node
void SceneNode::addChild(std::shared_ptr<SceneNode> child) {
    children.push_back(child);
}

// Set the transformation of this node
void SceneNode::setTransformation(const glm::mat4& transform) {
    transformation = transform;
}

// Get the local transformation matrix
glm::mat4 SceneNode::getTransformation() const {
    return transformation;
}

// Recursive rendering function (called by the SceneManager)
void SceneNode::render(const glm::mat4& parentTransform) {
    glm::mat4 globalTransform = parentTransform * transformation; // Combine parent's transformation with this node's
    // Render current node (if it has geometry, etc.)
    // Derived classes can override this to draw specific objects

    // Recursively render all children
    for (const auto& child : children) {
        child->render(globalTransform);
    }
}
