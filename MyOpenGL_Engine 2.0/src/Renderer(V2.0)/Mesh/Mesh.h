#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include<assimp/Importer.hpp>
#include "../../shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
    aiString path;  // We store the path of the texture to compare with other textures
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Mesh() = default;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> texture);
    void Draw(std::shared_ptr<Shader> shader, const glm::mat4& Translate);
    
    unsigned int GetVAO()const { return VAO; }
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};

