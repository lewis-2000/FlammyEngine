#include "shape_node.h"
#include "camera.h"
#include "multi_cam.h"
#include <glm/gtc/matrix_transform.hpp>  // For glm::perspective
#include <glm/matrix.hpp>
#include <iostream>

//Camera sceneCamera1;
MultiCam multiCam;

Camera sceneCamera1 = multiCam.selectCam(0);

float timeSinceLastSwitch = 0.0f;
float switchInterval = 5.0f;  // 5 seconds interval
int currentCameraIndex = 0;

void updateCamera(float deltaTime) {
    // Update the time since the last camera switch
    timeSinceLastSwitch += deltaTime;

    if (timeSinceLastSwitch >= switchInterval) {
        // Reset the timer
        timeSinceLastSwitch = 0.0f;

        // Switch to the next camera
        currentCameraIndex = (currentCameraIndex + 1) % multiCam.getNumCams();

        // Select the new camera and apply it to the scene
        sceneCamera1 = multiCam.selectCam(currentCameraIndex);
        std::cout << "Switched to camera: " << currentCameraIndex << std::endl;
    }
}



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
    std::cout << "LOG - RENDERING SCENE 1" << std::endl;

    getNumberOfChildren();


}

void ShapeNode::initShape() {
    // Vertex data for a cube (positions + colors + normals)
    float vertices[] = {
        // positions          // colors           // normals
        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  // bottom-left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,  // bottom-right
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, -1.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,  // top-left

        // Front face
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  1.0f,  // bottom-left
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  1.0f,  // bottom-right
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  1.0f,  // top-right
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  1.0f,  // top-left

        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,  0.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,  0.0f,  // top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, -1.0f, 0.0f,  0.0f,  // bottom-left
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,  0.0f,  // bottom-right

        // Right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f,  // top-left
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  0.0f,  // top-right
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f,  // bottom-right
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,  0.0f,  // bottom-left

         // Bottom face
         -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,  // top-right
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,  // top-left
          0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,  // bottom-left
         -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,  // bottom-right

         // Top face
         -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,  // top-left
          0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  // top-right
          0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,  // bottom-right
         -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f   // bottom-left
    };




    unsigned int indices[] = {
        // Back face
        0, 1, 2, 2, 3, 0,
        // Front face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Bottom face
        16, 17, 18, 18, 19, 16,
        // Top face
        20, 21, 22, 22, 23, 20
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // Unbind the VAO (not EBO or VBO)
    glBindVertexArray(0);
}

void ShapeNode::render(const glm::mat4& parentTransform) {
    // Calculate deltaTime for smooth movement
    float currentFrame = glfwGetTime();

    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;



    // Activate the shader
    shader.use();

    // Update the camera every frame
    updateCamera(deltaTime);

    // Process input
    processInput(glfwGetCurrentContext(), sceneCamera1, deltaTime);
    processMouseMovement(glfwGetCurrentContext(), sceneCamera1);
    //glfwSetScrollCallback(glfwGetCurrentContext(), scroll_callback);



    glClearColor(0.51f, 0.51f, 0.51f, 1.0f);


    // Retrieve the current window size dynamically
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    /*std::cout << "Light Position: "
        << "X: " << camera.Position.x << " "
        << "Y: " << camera.Position.y << " "
        << "Z: " << camera.Position.z << std::endl;*/


    // Light position
    glm::vec3 lightPos = sceneCamera1.Position;
    shader.setVec3("lightPos", lightPos);

    // Light color
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    shader.setVec3("lightColor", lightColor);

    // Camera (viewer) position
    shader.setVec3("viewPos", sceneCamera1.Position);

    shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f)); // Example shape color


    // Projection matrix (perspective) with dynamic aspect ratio based on window size
    glm::mat4 projection = glm::perspective(glm::radians(sceneCamera1.Zoom), (float)width / (float)height, 0.1f, 100.0f);
    shader.setMat4("projection", projection);



    // View matrix from the camera (move the camera back)
    glm::mat4 view = sceneCamera1.GetViewMatrix();
    shader.setMat4("view", view);


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

    clearChildren();


}