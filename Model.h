#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb/stb_image.h>

#include "Mesh.h"

#include <iostream>
#include <vector>

#include "utils.h"

#include "Bones.h"
#include "./Line.h"

using namespace std;

class Model
{
public:
    Model(const aiScene* scene);
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;	// sores all the textures loaded so far, optimization to make sure textures aren't loaded more than once

    void Draw(Shader &shader);

protected:

private:
    void loadModel(const aiScene* scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    unsigned int TextureFromFile(string path);
    void parse_mesh_bones(const aiMesh* pMesh);
    void parse_single_bone(int bone_index, const aiBone* pBone);
};

#endif // MODEL_H
