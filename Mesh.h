#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./inc/shader_s.h"

#include "Bones.h"

#define MAX_BONE_INFLUENCE 4
using namespace std;

struct Vertex
{
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
    unsigned int id;
    string type;
    string path;
};


class Mesh
{
public:
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;
    unsigned int VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    void Draw(Shader &shader);
    void setupMesh();

    aiMatrix4x4 mTransformation;

    vector<Bones> bones;
protected:

private:
    unsigned int VBO, EBO;
};

#endif // MESH_H
