#pragma once
#include "PxTransform.h"
#include "MeshLoader.h"
#include <SDL.h>
#include <quill/Backend.h>
#include <quill/Frontend.h>

using namespace quill;

class Render
{
public:
    Render():mLogger(nullptr), mWindow(nullptr) {}
    Render(Logger* logger, SDL_Window* window):mLogger(logger), mWindow(window) {}
    void Initialize();
    void SetupColors();
    void SetupLights();
    void RenderMesh(const Mesh& mesh);
    void RenderMeshes(const std::vector<Mesh>& meshes);
    void DrawMeshes(SDL_Window* window);

private:
    
    SDL_Window* mWindow;
    Logger* mLogger;
};
