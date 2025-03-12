#include "Engine.h"
#include<iostream>
#include "../Graphics/TextureManager.h"
#include"../Characters/Warrior.h"
#include"../Inputs/Input.h"
#include"../Timer/Timer.h"
#include"../Map/MapParser.h"
#include"../Camera/Camera.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

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

	if (!MapParser::GetInstance()->Load()) {
		std::cout << "Failed to load map" << std::endl;
		return false;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("Map");

	TextureManager::GetInstance()->Load("player", "assets/Idle.png");
	TextureManager::GetInstance()->Load("Walk", "assets/walk.png");
	TextureManager::GetInstance()->Load("bg", "assets/images/bg.png");

	player = new Warrior(new Properties("Walk", 300, 300, 22, 32));

	Camera::GetInstance()->SetTarget(player->GetOrigin());

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
	float dt = Timer::GetInstance()->GetDeltaTime();
	player->Update(dt);
	//m_LevelMap->Update();

	Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
	SDL_RenderClear(m_Renderer);
	SDL_SetRenderDrawColor(m_Renderer, 0, 100, 0, 255);

	TextureManager::GetInstance()->Draw("bg", 0, 0, 3500, 1961);
	m_LevelMap->Render();
	player->Draw();
	SDL_RenderPresent(m_Renderer);

	
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}
