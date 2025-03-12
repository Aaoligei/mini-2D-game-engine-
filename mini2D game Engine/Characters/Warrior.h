#pragma once
#include "Character.h"
#include"../Animation/Animation.h"
#include"../Physics/RigidBody.h"
#include "../Physics/Collider.h"

#define JUMP_FORCE 50.0f
#define JUMP_TIME 2.0f

class Warrior :
    public Character
{
public:
    Warrior() {};
    Warrior(Properties* props) :Character(props) {
		m_JumpTime = JUMP_TIME;
		m_JumpForce = JUMP_FORCE;

		m_Collider = new Collider();
		m_Collider->SetBuffer(0, 0, 0, 0);

        m_RigidBody = new RigidBody();
		m_RigidBody->SetGravity(3.0f);
        m_Animation = new Animation();
        m_Animation->SetProps(m_TextureID, 1, 11, 80, SDL_FLIP_NONE);
    }

    virtual void Draw() override;
    virtual void Clean() override;
    virtual void Update(float dt) override;

private:
    Animation* m_Animation;
    RigidBody* m_RigidBody;

    bool m_IsJumping;
	bool m_IsGrounded;

	float m_JumpForce;
	float m_JumpTime;

    Collider* m_Collider;
	Vector2D m_LastSafePosition;
};

