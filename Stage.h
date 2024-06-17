#ifndef STAGE_H
#define STAGE_H

#include "Model.h"
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class Stage
{
public:
    Stage(const char* path);
    void Render(Shader &shader);
    aiMatrix4x4 matrix4x4;

private:
    vector<Model> models;

};

#endif
