#include "shape_node.h"
#include <GLFW/glfw3.h>
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>  // For glm::perspective
#include <glm/matrix.hpp>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // You can also pass the camera as a parameter to the function if preferred

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

ShapeNode::ShapeNode(const Shader& shader) : shader(shader) {
    initShape();
}

void ShapeNode::initShape() {
    // Vertex data for a cube (positions + colors)
    float vertices[] = {
        // positions          // colors
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // bottom-left, back
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // bottom-right, back
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // top-right, back
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // top-left, back
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // bottom-left, front
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // bottom-right, front
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // top-right, front
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f   // top-left, front
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,  // back face
        4, 5, 6, 6, 7, 4,  // front face
        0, 3, 7, 7, 4, 0,  // left face
        1, 2, 6, 6, 5, 1,  // right face
        0, 1, 5, 5, 4, 0,  // bottom face
        3, 2, 6, 6, 7, 3   // top face
    };




    // Generate buffers and arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set element buffer (for indexing)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO (not EBO or VBO)
    glBindVertexArray(0);
}

void ShapeNode::render(const glm::mat4& parentTransform) {
    // Activate the shader
    shader.use();

    // View matrix from the camera (move the camera back)
    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    // Retrieve the current window size dynamically
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    // Projection matrix (perspective) with dynamic aspect ratio based on window size
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    // Render each cube
    for (unsigned int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);

        // Example: Apply rotation to the cube over time
        float angle = glfwGetTime() * 25.0f;  // Rotate the cube over time
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));  // Rotate around an arbitrary axis

        shader.setMat4("model", model);

        // Bind VAO and render the shape (e.g., cube)
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    // Recursively render children (if any)
    SceneNode::render(parentTransform);
}



ShapeNode::~ShapeNode() {
    // Clean up the buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}