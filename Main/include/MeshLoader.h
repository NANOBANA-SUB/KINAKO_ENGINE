#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <quill/Frontend.h>
#include <quill/Backend.h>
#include <glew.h>
#include <string>
#include <iostream>
#include <vector>

// メッシュを保持するための構造体
struct Mesh 
{
    std::vector<float> vertices; // 頂点座標
    std::vector<float> normals;  // 法線
    std::vector<float> texCoords; // テクスチャ座標
    std::vector<unsigned int> indices; // 頂点インデックス
};

class MeshLoader
{
public:
    MeshLoader();
    bool LoadModel(const std::string& path, std::vector<Mesh>& meshes);

private:
    quill::Logger* mLogger;
};