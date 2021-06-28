#include "Engine.h"
#include "Input.h"
#include "TextureManager.h"
#include "Timer.h"
#include "Warrior.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Engine* Engine::s_Instance = nullptr;

Warrior* player = nullptr;

bool Engine::Init()
{
    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0 )
    {
        SDL_Log("Failed to initialized SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("SDL Game Engine v0.0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    
    SDL_Log("Engine initialized!");

    SDL_Log("Loading textures...");
    TextureManager::GetInstance()->Load("player", "assets\\idle.png");
    TextureManager::GetInstance()->Load("player_run", "assets\\Run.png");

    // propriedades depende do altura e largura do spritesheet
    player = new Warrior(new Properties("player", 100, 200, 1280 / 8, 111));
    
    return m_IsRunning = true;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    player->Update(dt);
} 

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    player->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
    SDL_Log("Engine finished!");
    return true;
}

void Engine::Quit()
{
    m_IsRunning = false;
}
