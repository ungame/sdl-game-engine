#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Input
{
    public:
        static Input* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        bool GetMouseButtonDown(Uint8 mouseButton);

    private:
        Input();
        void KeyUp();
        void KeyDown();

        const Uint8* m_KeyStates;
        static Input* s_Instance;
        Uint8 m_MouseButton;
        bool m_MouseButtonDown, m_MouseButtonUp;
};

#endif