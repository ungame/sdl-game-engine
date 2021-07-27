// #include "Animation.h"
// #include "TextureManager.h"

// #include <SDL2/SDL.h>

// void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
// {
//     TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_CurrentFrame, flip);
// }

// void Animation::Update()
// {
//     m_CurrentFrame = (SDL_GetTicks() / m_Speed) % m_FrameCount;
// }



// void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed)
// {
//     m_Speed = speed;
//     m_TextureID = textureID;
//     m_SpriteRow = spriteRow;
//     m_FrameCount = frameCount;
// }
