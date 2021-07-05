#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Animation
{
    public:
        Animation() { };

        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

    private:
        int m_Speed;
        int m_SpriteRow;
        int m_FrameCount;
        int m_CurrentFrame;
        std::string m_TextureID;
};

#endif