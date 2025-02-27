#include "Warrior.h"
#include"../Graphics/TextureManager.h"
#include<SDL.h>

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
	m_Animation->Update();
	m_RigidBody->Update(0.2);
	m_RigidBody->ApplyForceX(5);
	m_Transform->Translate(Vector2D(m_RigidBody->GetPosition()));
}
