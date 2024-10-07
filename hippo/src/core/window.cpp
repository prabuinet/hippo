#include "core/window.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "engine.h"
#include "log.h"
#include <glad/glad.h>

hippo::core::Window::Window()
	: mWindow(nullptr)
{
}

hippo::core::Window::~Window()
{
	if (mWindow) {
		Shutdown();
	}
}

bool hippo::core::Window::Create()
{
	mWindow = SDL_CreateWindow("HippoGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!mWindow) {
		HIPPO_ERROR("Error creating window: {}", SDL_GetError());
		return false;
	}

#ifdef HIPPO_PLATFORM_MAC
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_SetWindowMinimumSize(mWindow, 200, 200);
	mGLContext = SDL_GL_CreateContext(mWindow);
	if (mGLContext == nullptr) {
		HIPPO_ERROR("Error creating opengl context: {}", SDL_GetError());
		return false;
	}

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	return true;
}

void hippo::core::Window::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;
}

void hippo::core::Window::PumpEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			Engine::Instance().Quit();
			break;
		default:
			break;
		}
	}
}

void hippo::core::Window::BeginRender()
{
	Engine::Instance().GetRenderManager().Clear();
}

void hippo::core::Window::EndRender()
{
	SDL_GL_SwapWindow(mWindow);
}
