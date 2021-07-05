#include "Input.h"
#include "Engine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Input* Input::s_Instance = nullptr;

Input::Input()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: Engine::GetInstance()->Quit(); break;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
            case SDL_MOUSEBUTTONDOWN: {
                m_MouseButtonDown = true;
                m_MouseButtonUp = !m_MouseButtonDown;
                m_MouseButton = event.button.button;
                break;
            };
            case SDL_MOUSEBUTTONUP: {
                m_MouseButtonUp = true;
                m_MouseButtonDown = !m_MouseButtonUp;
                m_MouseButton = event.button.button;
            }
           
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    return (m_KeyStates[key] == 1);
}

void Input::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

bool Input::GetMouseButtonDown(Uint8 mouseButton)
{
    return m_MouseButtonDown && m_MouseButton == mouseButton;
}