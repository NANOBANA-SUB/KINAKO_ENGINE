#pragma once
#include "Render.h"
#include <SDL.h>
#include <quill/Frontend.h>
#include <quill/Backend.h>

class Engine
{
public:
    Engine():mWindow(nullptr), mIsRunning(true), mLogger(nullptr){}
    bool Initialize();
    void RunLoop();
    void Shutdown();
    quill::Logger* GetLogger() const { return mLogger; }
    
private:
    bool QuillInitialize();
    bool ImGUIInitialize();
    void ImGUIFrameStart();
    void ImGUIRender();
    void ImGUIEnd();
    void ProcessInput();
    void UpdateEngine();
    void GenerateOutput();

    quill::Logger* mLogger;
    SDL_Window* mWindow;
    Render mRender;
    SDL_GLContext mContext;
    bool mIsRunning;
};