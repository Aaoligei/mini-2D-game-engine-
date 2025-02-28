#pragma once
#include "Character.h"
#include"../Animation/Animation.h"
#include"../Physics/RigidBody.h"
class Warrior :
    public Character
{
public:
    Warrior() {};
    Warrior(Properties* props) :Character(props) {
        m_RigidBody = new RigidBody();
        m_Animation = new Animation();
        m_Animation->SetProps(m_TextureID, 1, 11, 80, SDL_FLIP_NONE);
    }

    virtual void Draw() override;
    virtual void Clean() override;
    virtual void Update(float dt) override;

private:
    Animation* m_Animation;
    RigidBody* m_RigidBody;
};

