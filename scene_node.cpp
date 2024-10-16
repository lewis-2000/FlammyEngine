#include "scene_node.h"

// Constructor: initialize transformation to identity matrix
SceneNode::SceneNode()
    : transformation(glm::mat4(1.0f)),
    lastX(0.0f),   // Initialize lastX
    lastY(0.0f),   // Initialize lastY
    firstMouse(true) // Initialize firstMouse
{}


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


void SceneNode::processInput(GLFWwindow* window, Camera& camera, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
        //std::cout << "LOG - W KEY PRESSED" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
        //std::cout << "LOG - S KEY PRESSED" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
        //std::cout << "LOG - A KEY PRESSED" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
        //std::cout << "LOG - D KEY PRESSED" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}


void SceneNode::processMouseMovement(GLFWwindow* window, Camera& camera)
{
    // Get the window size from the current context
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // Get the current mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // If it's the first time processing the mouse movement, initialize the last positions
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // Calculate the offset in mouse movement
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;  // Reversed: y-coordinates go from bottom to top in OpenGL

    lastX = xpos;
    lastY = ypos;

    // Apply sensitivity scaling
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    // Update the camera's yaw and pitch based on the mouse movement
    camera.ProcessMouseMovement(xOffset, yOffset);
}

// mouse scroll wheel scrolls
void SceneNode::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    // Retrieve the SceneNode instance from the window user pointer
    SceneNode* sceneNode = static_cast<SceneNode*>(glfwGetWindowUserPointer(window));

    if (sceneNode) {
        // Access the camera from the sceneNode and process the scroll input
        sceneNode->camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }
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

// Clear all children from this node
void SceneNode::clearChildren() {
    children.clear();
    std::cout << "Child Scene Poped Out" << std::endl;
}

size_t SceneNode::getNumberOfChildren() const {
    return children.size();
}