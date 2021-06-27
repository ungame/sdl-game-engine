#include <iostream>
#include "Engine.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
   m_IsRunning = true; 

   return true;
}

bool Engine::Clean()
{
    return false;
}

void Engine::Quit()
{

}

void Engine::Update(float dt)
{
    std::cout << "updating..." << std::endl;
} 

void Engine::Render()
{

}

void Engine::Events()
{

}