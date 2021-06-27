#include "Warrior.h"
#include "TextureManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <windows.h>

Warrior::Warrior(Properties* props): Character(props)
{
    m_Row = 0;
    m_Frame = 0;
    m_FrameCount = 8;
    m_AnimSpeed = 80;
}

void Warrior::Log()
{
    std::cout << "TextureID: " << m_TextureID << std::endl;
    std::cout << "Dimension: " << m_Width << " x " << m_Height << std::endl;
    std::cout << "Row:       " << m_Row << std::endl;
    std::cout << "Frame:     " << m_Frame << std::endl;
    m_Transform->Log("Coordinates: ");
}

void Warrior::Draw()
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

void Warrior::Update(float dt)
{
    m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;

    if (m_Frame + 1 == m_FrameCount)
    {
        // Sleep(1000 * 3);
    }
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}  