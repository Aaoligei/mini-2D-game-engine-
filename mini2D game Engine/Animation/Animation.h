#pragma once
#include<string>
#include<SDL.h>

class Animation
{
public:
	Animation(){}

	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	int m_SpriteRow, m_SpriteFrame, m_AnimSpeed, m_FrameCount;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;
};

