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
    quill::Logger* GetLogger() const { return mLogger; }
    
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