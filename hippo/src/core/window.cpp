#include "core/window.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "engine.h"

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
	mWindow = SDL_CreateWindow("HippoGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (!mWindow) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return false;
	}

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
