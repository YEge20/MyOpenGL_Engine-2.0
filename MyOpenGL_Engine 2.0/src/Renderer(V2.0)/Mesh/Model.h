#pragma once
#include <GL/glew.h>
#include<glm/glm.hpp>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<memory>

#include "../../shader.h"
#include "Mesh.h"

class Model
{
public:
    /*  ³ÉÔ±º¯Êý   */
    Model(const std::string& path)
    {
        this->loadModel(path);
    }
    ~Model();
    void Draw(std::shared_ptr<Shader> shader, const glm::mat4& Translate);
    Texture GetTexture(int index);
    unsigned int GetTexture_MaxIndex()const;
private:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};