#include <SDL2/include/SDL.h>
#include <quill/Frontend.h>
#include <quill/Backend.h>

class Engine
{
public:
    Engine():mWindow(nullptr), mIsRunning(true), mLogger(nullptr){}
    bool Initialize();
    void RunLoop();
    void Shutdown();
    
private:
    bool QuillInitialize();
    void ProcessInput();
    void UpdateEngine();
    void GenerateOutput();

    quill::Logger* mLogger;
    SDL_Window* mWindow;
    SDL_GLContext mContext;
    bool mIsRunning;
};