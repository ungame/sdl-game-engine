#include "Engine.h"
#include "Input.h"
#include "TextureManager.h"
#include "Timer.h"
#include "Warrior.h"
#include "MapParser.h"
#include "Camera.h"
#include "Enemy.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Engine* Engine::s_Instance = nullptr;

// Warrior* player = nullptr;

bool Engine::Init()
{
    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0 )
    {
        SDL_Log("Failed to initialized SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("SDL Game Engine v0.0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
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

    if(!MapParser::GetInstance()->Load())
    {
        SDL_LogError(1, "Failed to load map");
        return 1;
    }

    SDL_Log("Load map success!");

    m_LevelMap = MapParser::GetInstance()->GetMap("MAP");

    SDL_Log("Loading textures...");
    TextureManager::GetInstance()->ParseTextures("assets/textures.tml");

    // propriedades depende do altura e largura do spritesheet
    Warrior* player = new Warrior(new Properties("player", 100, 200, 1280 / 8, 111));
    Enemy* enemy = new Enemy(new Properties("enemy", 820, 240, 32, 25));

    m_GameObjects.push_back(player);
    m_GameObjects.push_back(enemy);

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    
    return m_IsRunning = true;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();

    for(unsigned int i = 0; i < m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Update(dt);
    }

    Camera::GetInstance()->Update(dt);
} 

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    TextureManager::GetInstance()->Draw("bg", 0, 0, 2100, 1050, 2, 2, 0.4);
    m_LevelMap->Render();

    for(unsigned int i = 0; i < m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Draw();
    }

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
    for(unsigned int i = 0; i < m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Clean();
    }
    TextureManager::GetInstance()->Clean();
    MapParser::GetInstance()->Clean();
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
