#include "Warrior.h"
#include"../Graphics/TextureManager.h"
#include<SDL.h>
#include "../Inputs/Input.h"

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}

void Warrior::Update(float dt)
{
	bool isRight = true;
	m_Animation->Update();
	m_RigidBody->UnsetForce();
	
	m_Animation->SetProps("Walk", 1, 11, 80, isRight? SDL_FLIP_NONE: SDL_FLIP_HORIZONTAL);

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		m_RigidBody->ApplyForceX(-5);
		isRight = false;
		m_Animation->SetProps("Walk", 1, 13, 80, SDL_FLIP_HORIZONTAL);
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		m_RigidBody->ApplyForceX(5);
		isRight = true;
		m_Animation->SetProps("Walk", 1, 13, 80, SDL_FLIP_NONE);
	}
	m_RigidBody->Update(dt);
	m_Transform->TranslateX(Vector2D(m_RigidBody->GetPosition()).X);
}
