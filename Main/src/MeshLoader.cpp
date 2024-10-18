#include "../include/MeshLoader.h"
#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include "quill/sinks/ConsoleSink.h"

MeshLoader::MeshLoader():mLogger(nullptr)
{
    try
    {
        quill::BackendOptions backend_options;
        quill::Backend::start(backend_options);

        auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1");
        mLogger = quill::Frontend::create_or_get_logger("root", std::move(console_sink));

        LOG_INFO(mLogger, "Quill initialize completed.");
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(mLogger, "Failed to initialize Quill.", 1);
    }
}

bool MeshLoader::LoadModel(const std::string& path, std::vector<Mesh>& meshes)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        LOG_ERROR(mLogger, "Failed to Initialize Assimp.", 1);
        return false;
    }

    // メッシュの読み込み
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) 
    {
        aiMesh* mesh = scene->mMeshes[i];

        Mesh myMesh;

        // 頂点座標
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) 
        {
            myMesh.vertices.push_back(mesh->mVertices[j].x);
            myMesh.vertices.push_back(mesh->mVertices[j].y);
            myMesh.vertices.push_back(mesh->mVertices[j].z);

            if (mesh->HasNormals()) 
            {
                myMesh.normals.push_back(mesh->mNormals[j].x);
                myMesh.normals.push_back(mesh->mNormals[j].y);
                myMesh.normals.push_back(mesh->mNormals[j].z);
            }

            if (mesh->mTextureCoords[0]) 
            {
                myMesh.texCoords.push_back(mesh->mTextureCoords[0][j].x);
                myMesh.texCoords.push_back(mesh->mTextureCoords[0][j].y);
            }
        }

        // インデックス（頂点インデックス）
        for (unsigned int j = 0; j < mesh->mNumFaces; j++) 
        {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++) 
            {
                myMesh.indices.push_back(face.mIndices[k]);
            }
        }

        meshes.push_back(myMesh);
    }

    return true;
}