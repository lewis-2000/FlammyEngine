#ifndef SCENE_NODE_H
#define SCENE_NODE_H


#include "camera.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>  // For math and matrix operations
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

class SceneNode {
public:
    // Constructor
    SceneNode();

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    // Mouse settings
    bool firstMouse = true;
    float lastX, lastY;
    float sensitivity = 0.1f;  // Adjust this to control how sensitive the camera is to mouse movements

    Camera camera;

    // Add a child node
    void addChild(std::shared_ptr<SceneNode> child);

    // Set the transformation (e.g., position)
    void setTransformation(const glm::mat4& transform);

    // Get the transformation of this node
    glm::mat4 getTransformation() const;

    //inputs
    void processInput(GLFWwindow* window, Camera& camera, float deltaTime);
    void processMouseMovement(GLFWwindow* window, Camera& camera);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


    // Traverse and render the scene graph (recursive)
    virtual void render(const glm::mat4& parentTransform);

    void clearChildren();

    size_t getNumberOfChildren() const;

protected:
    glm::mat4 transformation; // Local transformation matrix

    std::vector<std::shared_ptr<SceneNode>> children; // Child nodes
};

#endif // !SCENE_NODE_H