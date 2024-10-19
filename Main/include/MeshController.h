#pragma once
#include "MeshLoader.h"
#include <glm.hpp>
#include <imgui/imgui.h>
#include <vector>

class MeshController
{
public:
    MeshController();
    void RenderUI();
    void ApplyTransforms(std::vector<Mesh>& meshes);

private:
    glm::vec3 mTranslation;
    float mScale;
};