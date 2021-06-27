#include "Engine.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0 )
    {
        SDL_Log("Failed to initialized SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Game Engine v0.0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if ( m_Window == nullptr )
    {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if ( m_Renderer == nullptr )
    {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }
    
    std::cout << "Engine initialized!" << std::endl;

   return m_IsRunning = true;
}

void Engine::Update(float dt)
{
} 

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        Quit();
        break;
    
    default:
        break;
    }
}

bool Engine::Clean()
{
    return false;
}

void Engine::Quit()
{
    m_IsRunning = false;
    SDL_Quit();
    std::cout << "Engine finished!" << std::endl;
}
