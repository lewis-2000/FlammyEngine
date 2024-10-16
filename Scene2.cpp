#include "Scene2.h"
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>  // For glm::perspective
#include <glm/matrix.hpp>
#include <iostream>

Camera sceneCamera2(glm::vec3(0.0f, 2.0f, 1.0f));


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// Mouse settings
bool firstMouse = true;
float lastX, lastY;
float sensitivity = 0.1f;  // Adjust this to control how sensitive the camera is to mouse movements


//Camera camera(glm::vec3(0.0f, 2.0f, 1.0f));  // You can also pass the camera as a parameter to the function if preferred

glm::vec3 newPositions[] = {
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


Scene2::Scene2(const Shader& shader) : shader(shader) {
    initShape();
    std::cout << "LOG - RENDERING SCENE 2" << std::endl;


    getNumberOfChildren();


}


void Scene2::initShape() {
    // Vertex data for a cube (positions + colors + normals)
    float vertices[] = {
        // positions          // colors           // normals
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  // back face
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
        // (Repeat for other faces with appropriate normals)
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

void Scene2::render(const glm::mat4& parentTransform) {
    // Activate the shader
    shader.use();

    // Process input
    processInput(glfwGetCurrentContext(), sceneCamera2, deltaTime);
    processMouseMovement(glfwGetCurrentContext(), sceneCamera2);
    //glfwSetScrollCallback(glfwGetCurrentContext(), scroll_callback);

    glClearColor(0.51f, 0.51f, 0.51f, 1.0f);

    // View matrix from the camera (move the camera back)
    glm::mat4 view = sceneCamera2.GetViewMatrix();
    shader.setMat4("view", view);

    // Retrieve the current window size dynamically
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    // Projection matrix (perspective) with dynamic aspect ratio based on window size
    glm::mat4 projection = glm::perspective(glm::radians(sceneCamera2.Zoom), (float)width / (float)height, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    // Light position
    glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, -10.0f);
    shader.setVec3("lightPos", lightPos);

    //Check uniform values
   /* std::cout << "lightPos location: " << glGetUniformLocation(shader.ID, "lightPos") << std::endl;
    std::cout << "lightColor location: " << glGetUniformLocation(shader.ID, "lightColor") << std::endl;
    std::cout << "viewPos location: " << glGetUniformLocation(shader.ID, "viewPos") << std::endl;
    std::cout << "objectColor location: " << glGetUniformLocation(shader.ID, "objectColor") << std::endl;*/




    // Light color
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    shader.setVec3("lightColor", lightColor);

    // Camera (viewer) position
    shader.setVec3("viewPos", sceneCamera2.Position);

    shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f)); // Example color



    // Render each cube
    for (unsigned int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, newPositions[i]);

        // Example: Apply rotation to the cube over time
        float angle = glfwGetTime() * 25.0f;  // Rotate the cube over time
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));  // Rotate around an arbitrary axis

        shader.setMat4("model", model);

        //std::cout << "LOG - Cube angle: " << angle << std::endl;


        // Bind VAO and render the shape (e.g., cube)
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    // Recursively render children (if any)
    SceneNode::render(parentTransform);
}



Scene2::~Scene2() {
    // Clean up the buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    clearChildren();
}