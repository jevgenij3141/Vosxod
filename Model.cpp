#include "Model.h"

Model::Model(const aiScene* scene)
{
    loadModel(scene);
}

void Model::Draw(Shader &shader)
{
//    Shader lineShader("./includes/line_shader.vs", "./includes/line_shader.fs");
//
//    for(unsigned int i = 0; i < meshes.size(); i++){
//        glm::mat4 model = glm::mat4(1.0f);
//
//        model = glm::translate(model, glm::vec3(meshes[i].mTransformation.a4, meshes[i].mTransformation.b4, meshes[i].mTransformation.c4));
//        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//
//        //model = glm::translate(model, meshes[i].mTransformation.b2, meshes[i].mTransformation.b3, meshes[i].mTransformation.b4);
//        shader.setMat4("model", model);
//
//        //meshes[i].Draw(shader);
//
//        Line line;
//
//        for(unsigned int a = 0; a < meshes[i].bones.size(); a++){
//
//            Bones bone = meshes[i].bones[a];
//
//            shader.use();
//            line.setLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(bone.mTransformation.b4, bone.mTransformation.c4, bone.mTransformation.d4));
//            line.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
//            //lineShader.setMat4("projection", projection);
//            shader.setMat4("model", model);
//            //lineShader.setMat4("view", view);
//            line.draw(shader);
//        }
//    }
}

void Model::loadModel(const aiScene* scene)
{
    glm::mat4 globalInverseTransform = assimpToGlmMatrix(scene->mRootNode->mTransformation);
    globalInverseTransform = glm::inverse(globalInverseTransform);




    // read file via ASSIMP
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//    // check for errors
//    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
//    {
//        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
//        return;
//    }
//printf("mPositionKeys: %.05f %.05f %.05f %.05f \n", scene->mRootNode->mTransformation.a1, scene->mRootNode->mTransformation.a2, scene->mRootNode->mTransformation.a3, scene->mRootNode->mTransformation.a4);

//    printf("mNumMeshes: %d \n", scene->mNumMeshes);
//    for(unsigned int a = 0; a < scene->mNumMeshes; a++){
//        printf("mNumBones: %d \n", scene->mMeshes[a]->mNumBones);
//        for(unsigned int b = 0; b < scene->mMeshes[a]->mNumBones; b++){
//            printf("mBones: %s \n", scene->mMeshes[a]->mBones[b]->mName.C_Str());
//            printf("mBones.mNode: %.05f \n", scene->mMeshes[a]->mBones[b]->mOffsetMatrix.d3);
//        }
//    }
//
//    printf("mNumAnimations: %d \n", scene->mNumAnimations);
//    for(unsigned int a = 0; a < scene->mNumAnimations; a++){
//        printf("mNumChannels: %d \n", scene->mAnimations[a]->mNumChannels);
//        for(unsigned int b = 0; b < scene->mAnimations[a]->mNumChannels; b++){
//            printf("mNumChannels: %s %d \n", scene->mAnimations[a]->mName.C_Str(), scene->mAnimations[a]->mNumChannels);
//            for(unsigned int c = 0; c < scene->mAnimations[a]->mChannels[b]->mNumRotationKeys; c++){
//                aiQuaternion q = scene->mAnimations[a]->mChannels[b]->mRotationKeys[c].mValue;
//                printf("mRotationKeys: %.05f %.05f %.05f %.05f \n", q.GetMatrix().a1, q.y, q.z, q.w);
//
//                aiVector3D q1 = scene->mAnimations[a]->mChannels[b]->mPositionKeys[c].mValue;
//                printf("mPositionKeys: %.05f %.05f %.05f \n", q1.x, q1.y, q1.z);
//
//                aiVector3D q2 = scene->mAnimations[a]->mChannels[b]->mScalingKeys[c].mValue;
//                printf("mScalingKeys: %.05f %.05f %.05f \n", q2.x, q2.y, q2.z);
//            }
//        }
//    }

    //printf("mNumMeshes: %d \n", scene->mNumMeshes);

    // load model mesh
    for(unsigned int a = 0; a < scene->mNumMeshes; a++)
    {
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        aiMesh* mesh = scene->mMeshes[a];

        for(unsigned int b = 0; b < mesh->mNumVertices; b++)
        {
            Vertex vertex;
            glm::vec3 vector;

            // positions
            vector.x = mesh->mVertices[b].x;
            vector.y = mesh->mVertices[b].y;
            vector.z = mesh->mVertices[b].z;
            vertex.Position = vector;

            // normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[b].x;
                vector.y = mesh->mNormals[b].y;
                vector.z = mesh->mNormals[b].z;
                vertex.Normal = vector;
            }

            // texture coordinates
            if(mesh->mTextureCoords[0])
            {
                glm::vec2 vec;

                vec.x = mesh->mTextureCoords[0][b].x;
                vec.y = mesh->mTextureCoords[0][b].y;
                vertex.TexCoords = vec;

                // tangent
                vector.x = mesh->mTangents[b].x;
                vector.y = mesh->mTangents[b].y;
                vector.z = mesh->mTangents[b].z;
                vertex.Tangent = vector;

                // bitangent
                vector.x = mesh->mBitangents[b].x;
                vector.y = mesh->mBitangents[b].y;
                vector.z = mesh->mBitangents[b].z;
                vertex.Bitangent = vector;
            }
            else
            {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);

            // indices
            for(unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];

                for(unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }

            // materials
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            // 1. diffuse maps
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            // 2. specular maps
            std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            // 3. normal maps
            std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            // 4. height maps
            std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        }

        Mesh newMesh = Mesh(vertices, indices, textures);
        newMesh.mTransformation = scene->mRootNode->mChildren[a]->mTransformation;



        // parse bones


//        if (mesh->HasBones()) {
//
//            for (unsigned int a = 0 ; a < mesh->mNumBones ; a++) {
//
//                const aiBone* pBone = mesh->mBones[a];
//
//                Bones newBone;
//                newBone.mTransformation = pBone->mOffsetMatrix;
//                newMesh.bones.push_back(newBone);
//
//                for (unsigned int b = 0 ; b < pBone->mNumWeights ; b++) {
//                    if (b == 0) printf("\n");
//                    const aiVertexWeight& vw = pBone->mWeights[b];
//                }
//
//            }
//        }

        newMesh.setupMesh();
        meshes.push_back(newMesh);
    }
}

void Model::parse_mesh_bones(const aiMesh* pMesh)
{
    printf("Parse bone ---------------------------------> \n");
    for (unsigned int i = 0 ; i < pMesh->mNumBones ; i++)
    {
        parse_single_bone(i, pMesh->mBones[i]);
    }
}

void Model::parse_single_bone(int bone_index, const aiBone* pBone)
{
    printf("      Bone %d: '%s' num vertices affected by this bone: %d\n", bone_index, pBone->mName.C_Str(), pBone->mNumWeights);
    printf("        Matrix: b1: %.04f b2: %.04f b3: %.04f b4: %.04f \n", pBone->mOffsetMatrix.b1, pBone->mOffsetMatrix.b2, pBone->mOffsetMatrix.b3, pBone->mOffsetMatrix.b4);

    for (unsigned int i = 0 ; i < pBone->mNumWeights ; i++)
    {
        if (i == 0) printf("\n");
        const aiVertexWeight& vw = pBone->mWeights[i];
        printf("       %d: vertex id %d weight %.2f\n", i, vw.mVertexId, vw.mWeight);
    }

    printf("\n");
}
vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {
            // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str());
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

unsigned int Model::TextureFromFile(string path)
{
    string filename = "./src/"+string(path);

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
