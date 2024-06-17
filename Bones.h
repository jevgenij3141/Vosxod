#ifndef BONES_H
#define BONES_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Bones
{
public:
    Bones();
    aiMatrix4x4 mTransformation;

private:
};

#endif
