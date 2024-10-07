#include <hippo/engine.h>
#include <iostream>
#include <sdl2/SDL.h>
#include "log.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"

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

            float vertices[]
            {
                -0.5f, -0.5f, 0.f,
                  0.f,  0.5f, 0.f,
                 0.5f, -0.5f, 0.f
            };

            std::shared_ptr<graphics::Mesh> mesh = std::make_shared<graphics::Mesh>(&vertices[0], 3, 3);

            const char* vertexShader = R"(
                #version 410 core
                layout (location=0) in vec3 position;
                out vec3 vpos;
                void main()
                {
                    vpos = position + vec3(0.5, 0.5, 0);
                    gl_Position = vec4(position, 1.0);
                }
            )";

            const char* fragmentShader = R"(
                #version 410 core
                out vec4 outColor;
                in vec3 vpos;

                uniform vec3 color = vec3(0.0);
                void main()
                {
                    outColor = vec4(vpos, 1.0);
                }
            )";

            std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>(vertexShader, fragmentShader);
            shader->SetUniformFloat3("color", 1, 0, 0);

            while (mIsRunning) {
                mWindow.PumpEvents();
                mWindow.BeginRender();

                auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh, shader);
                mRenderManager.Submit(std::move(rc));

                mRenderManager.Flush();

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

                // initialize managers
                mRenderManager.Initialize();

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
        mRenderManager.Shutdown();
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