#include <hippo/engine.h>
#include <iostream>
#include <sdl2/SDL.h>
#include "log.h"

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

                mWindow.BeginRender();
                mWindow.EndRender();
            }

            Shutdown();
        }
    }

    bool Engine::Initialize()
    {
        bool ret = false;

        mLogManager.Initialize();

        HIPPO_ASSERT(!mIsInitialized, "attempting to initialize twice");

        GetInfo();

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            HIPPO_ERROR("sdl initialization failed: {}", SDL_GetError());
        }
        else {
            SDL_version version;
            SDL_VERSION(&version);
            HIPPO_INFO("SDL Version: {}.{}.{}", 
                static_cast<int32_t>(version.major),
                static_cast<int32_t>(version.minor),
                static_cast<int32_t>(version.patch));

            if (mWindow.Create()) {
                ret = true;
                mIsRunning = true;
                mIsInitialized = true;
            }
        }

        if (!ret) {
            HIPPO_ERROR("engine initialization failed. shutting down.");
        }

        return ret;
    }

    void Engine::Shutdown()
    {
        mIsRunning = false;
        mIsInitialized = false;

        // managers - usually shutdown in reverse order
        mLogManager.Shutdown();

        mWindow.Shutdown();
        SDL_Quit();
    }

    void Engine::GetInfo() {
        HIPPO_TRACE("HippoEngine: v{}.{}", 0, 1);

        #ifdef HIPPO_CONFIG_DEBUG
        HIPPO_DEBUG("Configuration: Debug");
        #endif

        #ifdef HIPPO_CONFIG_RELEASE
        HIPPO_DEBUG("Configuration: Release");
        #endif

        #ifdef HIPPO_PLATFORM_WINDOWS
        HIPPO_DEBUG("Platform: Windows");
        #endif

        #ifdef HIPPO_PLATFORM_LINUX
        HIPPO_DEBUG("Platform: Linux");
        #endif
    }

    Engine::Engine()
        : mIsRunning(false) 
        , mIsInitialized(false)
    {
        
    }
}