#pragma once
#include "../include/Engine.h"
#include "../include/MeshLoader.h"
#include "../include/MeshController.h"
#include <glew.h>
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include <quill/sinks/ConsoleSink.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl2.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <iostream>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

bool Engine::Initialize()
{
    // Quill初期化
    if (QuillInitialize() != true) return false;
    // SDL初期化
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        LOG_ERROR(mLogger, "Failed to initialize SDL:", SDL_GetError());
        return false;
    }

    // OpenGLプロファイル
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    mWindow = SDL_CreateWindow("KINAKO ENGINE", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    if (!mWindow)
    {
        LOG_ERROR(mLogger, "Failed to initialize window:", SDL_GetError());
        return false;
    }

    mContext = SDL_GL_CreateContext(mWindow);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        LOG_ERROR(mLogger, "Failed to initialize GLEW.", 2);
        return false;
    }

    glGetError();

    // ImGUI初期化
    if (ImGUIInitialize() != true)
    {
        LOG_ERROR(mLogger, "Failed to initialize ImGui:", 1000-3);
        return false;
    }

    return true;
}

void Engine::RunLoop()
{
    MeshLoader meshLoader;
    mRender = Render(mLogger, mWindow);

    std::vector<Mesh> originalMeshes;
    std::vector<Mesh> editMeshes;

    MeshController meshController;
    if (meshLoader.LoadModel("./models/test.obj", originalMeshes))
        editMeshes = originalMeshes;

    while (mIsRunning)
    {
        ProcessInput();

        ImGUIFrameStart();

        editMeshes = originalMeshes;
        meshController.RenderUI();
        meshController.ApplyTransforms(editMeshes);
        
        ImGUIRender();
        
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        mRender.RenderMeshes(editMeshes); 

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(mWindow);
    }
    
    ImGUIEnd();
}

void Engine::Shutdown()
{
    SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

bool Engine::QuillInitialize()
{
    try
    {
        quill::BackendOptions backend_options;
        quill::Backend::start(backend_options);

        auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1");
        mLogger = quill::Frontend::create_or_get_logger("root", std::move(console_sink));

        LOG_INFO(mLogger, "Quill initialize completed.");

        return true;
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(mLogger, "Failed to initialize Quill.", 1);
        return false;
    }
}

bool Engine::ImGUIInitialize()
{
    try
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(mWindow, mContext);
        ImGui_ImplOpenGL3_Init("#version 130");

        LOG_INFO(mLogger, "ImGui initialize completed.");
        return true;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR(mLogger, "Failed to initialize ImGUI.", 1);
        return false;
    }
}

void Engine::ImGUIFrameStart()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void Engine::ImGUIRender()
{
    ImGui::Render();
}

void Engine::ImGUIEnd()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Engine::ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
    }

    const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}