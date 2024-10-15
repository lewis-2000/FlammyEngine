#ifndef SCENE_NODE_2
#define SCENE_NODE_2


#include "shader.h"
#include "scene_node.h"


class Scene2 : public SceneNode {
public:
    Scene2(const Shader& shader);

    // Override render to draw the shape
    virtual void render(const glm::mat4& parentTransform) override;

    //Destructor
    ~Scene2();


private:
    Shader shader;  // Shader for rendering the shape
    unsigned int VAO; // Vertex Array Object
    unsigned int VBO; // Vertex Buffer Object
    unsigned int EBO; // Element Buffer Object

    // Initialize the geometry (vertices) of the shape
    void initShape();
};

#endif // !SCENE_NODE_2
