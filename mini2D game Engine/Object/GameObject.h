#pragma once
#include"IObject.h"
#include "../Physics/Transform.h"
#include <string>
#include <SDL.h>
#include"../Physics/Vector2D.h"

struct Properties {
public:
    std::string TextureID;
    int Width, Height;
    float X, Y;
    SDL_RendererFlip Flip;

    Properties(std::string textureID,int x,int y,int width,int height,SDL_RendererFlip flip=SDL_FLIP_NONE) 
    :TextureID(textureID),
    Width(width),Height(height),
    X(x),Y(y),Flip(flip){

    }
};

class GameObject :
    public IObject
{
public:
    GameObject(Properties* props):
        m_TextureID(props->TextureID),
        m_Width(props->Width),m_Height(props->Height),
        m_Flip(props->Flip){
        m_Transform = new Transform(props->X, props->Y);

        float px = props->X + props->Width / 2.0f;
		float py = props->Y + props->Height / 2.0f;
        m_Origin = new Point(px,py);
    }

	inline Point* GetOrigin() const {
		return m_Origin;
	}

    // ͨ�� IObject �̳�
    void Draw() override {

    }
    void Update(float dt) override {

    }
    void Clean() override {

    }

protected:
    Point* m_Origin;
    Transform* m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};

