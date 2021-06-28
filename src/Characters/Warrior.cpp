#include "Warrior.h"
#include "TextureManager.h"
#include "Animation.h"
#include "RigidBody.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <windows.h>

Warrior::Warrior(Properties* props): Character(props)
{
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 8, 80, SDL_FLIP_HORIZONTAL);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
    m_RigidBody->Update(0.4);
    m_RigidBody->ApplyForceX(5);
    
    m_Transform->TranslateX(m_RigidBody->Position().X);
    m_Transform->TranslateY(m_RigidBody->Position().Y);

    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}  
