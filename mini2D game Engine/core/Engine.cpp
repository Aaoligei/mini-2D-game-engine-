#include "Engine.h"
#include<iostream>
#include "../Graphics/TextureManager.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	TextureManager::GetInstance()->Load("1", "assets/image.png");
	return m_IsRunning = true;
}

void Engine::Clean()
{
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	TextureManager::GetInstance()->Clean();
	SDL_Quit();
	IMG_Quit();
}

void Engine::Quit()
{
	m_IsRunning = false;
}

void Engine::Update()
{
	
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 100, 100, 0, 255);
	SDL_RenderClear(m_Renderer);
	
	TextureManager::GetInstance()->Draw("1",0, 0, 512, 512);
	SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:Quit();
		break;
	}
}
