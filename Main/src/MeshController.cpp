#include "../include/MeshController.h"
#include "imgui/imgui.h"

MeshController::MeshController()
:mTranslation(0.0f, 0.0f, 0.0f), mScale(1.0f)
{

}

void MeshController::RenderUI()
{
    ImGui::Begin("Mesh Transformation");

    // スライダーで平行移動
    ImGui::SliderFloat3("Translation", &mTranslation.x, -1.0f, 1.0f);

    // スライダーで拡大縮小
    ImGui::SliderFloat("Scale", &mScale, 0.1f, 10.0f);

    ImGui::End();
}

void MeshController::ApplyTransforms(std::vector<Mesh>& meshes)
{   
    // 平行移動
    for (auto& mesh : meshes)
    {
        for (size_t i = 0; i < mesh.vertices.size(); i+= 3)
        {
            mesh.vertices[i] += mTranslation.x;
            mesh.vertices[i + 1] += mTranslation.y;
            mesh.vertices[i + 2] += mTranslation.z;
        }
    }

    // スケーリング
    for (auto& mesh : meshes)
    {
        for (size_t i = 0; i < mesh.vertices.size(); i += 3)
        {
            mesh.vertices[i] *= mScale;
            mesh.vertices[i + 1] *= mScale;
            mesh.vertices[i + 2] *= mScale;
        }
    }
}