#include "Warrior.h"
#include"../Graphics/TextureManager.h"
#include<SDL.h>
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionHandler.h"

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(),&box);
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}

void Warrior::Update(float dt)
{
	bool isRight = true;

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

	//ÌøÔ¾
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K) && m_IsGrounded) {
		m_IsJumping = true;
		m_IsGrounded = false;
		m_RigidBody->ApplyForceY( -m_JumpForce);
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K) && m_IsJumping && m_JumpTime > 0) {
		m_JumpTime -= dt;
		m_RigidBody->ApplyForceY( -m_JumpForce);
	}
	else {
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}

	//xÖáÒÆ¶¯
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->GetPosition().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 22, 32);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}

	//yÖáÒÆ¶¯
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 22, 32);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else {
		m_IsGrounded = false;
	}


	m_Origin->X = m_Transform->X + m_Width / 2.0f;
	m_Origin->Y = m_Transform->Y + m_Height / 2.0f;
	m_Animation->Update();
}
