#include <hippo/engine.h>
#include <iostream>
#include <sdl2/SDL.h>

namespace hippo {

    Engine* Engine::mInstance = nullptr;

    Engine& Engine::Instance() {
        if (mInstance == nullptr)
            mInstance = new Engine();

        return *mInstance;
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
        if (Initialize()) {

            while (mIsRunning) {
                mWindow.PumpEvents();
            }

            Shutdown();
        }
    }

    bool Engine::Initialize()
    {
        bool ret = false;

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            std::cout << "sdl initialization failed: " << SDL_GetError() << std::endl;            
        }
        else {
            SDL_version version;
            SDL_VERSION(&version);
            std::cout << "SDL Version: " << static_cast<int32_t>(version.major)
                << "." << static_cast<int32_t>(version.minor)
                << "." << static_cast<int32_t>(version.patch) << "\n";

            if (mWindow.Create()) {
                ret = true;
                mIsRunning = true;
            }
        }

        if (!ret) {
            std::cout << "engine initialization failed. shutting down." << std::endl;
        }

        return ret;
    }

    void Engine::Shutdown()
    {
        mIsRunning = false;
        mWindow.Shutdown();
        SDL_Quit();
    }

    void Engine::GetInfo() {
        #ifdef HIPPO_CONFIG_DEBUG
        std::cout << "Configuration: Debug" << std::endl;
        #endif

        #ifdef HIPPO_CONFIG_RELEASE
        std::cout << "Configuration: Release" << std::endl;
        #endif

        #ifdef HIPPO_PLATFORM_WINDOWS
        std::cout << "Platform: Windows" << std::endl;
        #endif

        #ifdef HIPPO_PLATFORM_LINUX
        std::cout << "Platform: Linux" << std::endl;
        #endif
    }

    Engine::Engine()
        : mIsRunning(false) 
    {
        GetInfo();
    }
}