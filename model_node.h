// ModelNode.h (Derived from SceneNode)
#include "shader.h"
#include "scene_node.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <vector>

class ModelNode : public SceneNode {
public:
    ModelNode(const std::string& path, const Shader& shader);

    void loadModel(const std::string& path);
    void render(const glm::mat4& parentTransform = glm::mat4(1.0f)) override;

private:
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Mesh> meshes;
    Shader shader;
};

