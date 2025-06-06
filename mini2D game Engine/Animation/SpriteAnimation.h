#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "SDL.h"
#include "AnimationNew.h"

class SpriteAnimation : public Animation {

public:
    SpriteAnimation(bool repeat = true);

    virtual void Update(float dt);
    void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

private:
    int m_Speed;
    int m_SpriteRow;
    int m_FrameCount;
    std::string m_TextureID;
};

#endif // SPRITEANIMATION_H