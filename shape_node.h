#pragma once
#ifndef SHAPE_NODE_H
#define SHAPE_NODE_H


#include "shader.h"
#include "scene_node.h"


class ShapeNode : public SceneNode {
public:
    ShapeNode(const Shader& shader);

    // Override render to draw the shape
    virtual void render(const glm::mat4& parentTransform) override;

    //Destructor
    ~ShapeNode();


private:
    Shader shader;  // Shader for rendering the shape
    unsigned int VAO; // Vertex Array Object
    unsigned int VBO; // Vertex Buffer Object
    unsigned int EBO; // Element Buffer Object

    // Initialize the geometry (vertices) of the shape
    void initShape();
};

#endif // !SHAPE_NODE_H
