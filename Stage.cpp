#include "Stage.h"

Stage::Stage(const char* path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }

    this->matrix4x4 = scene->mRootNode->mTransformation;

    Model model(scene);

    this->models.push_back(model);
}

void Stage::Render(Shader &shader)
{
    for(unsigned int a = 0; a < this->models.size(); a++)
    {
        this->models[a].Draw(shader);
    }
}
