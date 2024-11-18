#include "Input.h"

#include <SDL_events.h>

glm::ivec2 bin::Input::GetMousePosition()
{
    glm::ivec2 mousePosition{};
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    return mousePosition;
}

Uint32 bin::Input::GetMouseState() { return SDL_GetMouseState({}, {}); }

bool bin::InputAction::HasKeyboardKey(SDL_Scancode compareKey) const
{
    return std::ranges::count(keyboardButtons, compareKey) > 0;
}

void bin::Input::ProcessInput(bool& shouldQuit)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                shouldQuit = true;
                break;
            }
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                const ButtonState buttonState = event.type == SDL_KEYDOWN ? ButtonState::Down : ButtonState::Up;
                for(auto&& bind : m_Binds)
                {
                    if(event.key.repeat)
                        continue;

                    if(not bind->inputActionPtr->HasKeyboardKey(event.key.keysym.scancode))
                        continue;

                    bind->inputEvent.Invoke(InputContext{ buttonState });
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                const ButtonState buttonState = event.type == SDL_MOUSEBUTTONDOWN ? ButtonState::Down : ButtonState::Up;
                for(auto&& bind : m_Binds)
                {
                    if(event.key.repeat)
                        continue;

                    if(bind->inputActionPtr->leftMouseButton and event.button.button == 1)
                        bind->inputEvent.Invoke(InputContext{ buttonState });

                    if(bind->inputActionPtr->rightMouseButton and event.button.button == 2)
                        bind->inputEvent.Invoke(InputContext{ buttonState });
                }
                break;
            }
        }
    }
}


