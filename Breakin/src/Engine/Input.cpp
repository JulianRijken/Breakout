#include "Input.h"

#include <SDL_events.h>

void bin::Input::ProcessInput(bool& shouldQuit)
{

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            shouldQuit = true;
            continue;
        }

        if(HandleKeyboardEvent(event))
            continue;
    }
}

bool bin::Input::HandleKeyboardEvent(const SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            const ButtonState buttonState = event.type == SDL_KEYDOWN ? ButtonState::Down : ButtonState::Up;
            for(auto&& bind : m_Binds)
            {
                if(event.key.repeat)
                    continue;

                if(bind->TryExecuteKeyboard(buttonState, event.key.keysym.scancode))
                    continue;
            }
            return true;
    }
    return false;
}

bool bin::InputBinding::TryExecuteKeyboard(ButtonState buttonState, SDL_Scancode compareKey)
{
    if(not inputActionPtr->HasKeyboardKey(compareKey))
        return false;

    inputEvent.Invoke(InputContext{ buttonState });
    return true;
}

bool bin::InputAction::HasKeyboardKey(SDL_Scancode compareKey) const
{
    return std::ranges::count(keyboardButtons, compareKey) > 0;
}

bool bin::InputAction::HasControllerButton(SDL_GameControllerButton compareButton) const
{
    return std::ranges::count(controllerButtons, compareButton) > 0;
}
