#ifndef INPUT_H
#define INPUT_H

#include <SDL_events.h>
#include <SDL_gamecontroller.h>
#include <SDL_scancode.h>

#include <glm/vec2.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Event.h"
#include "Singleton.h"

namespace bin
{
    enum class ButtonState
    {
        Down,
        Up
    };

    struct InputContext final
    {
        // Abstracted to allow for future changes
        // Like passing the value of a gamepad trigger
        ButtonState state;
    };

    // The the action linking seperating the action and the keys
    struct InputAction final
    {
        std::vector<SDL_Scancode> keyboardButtons;
        std::vector<SDL_GameControllerButton> controllerButtons;

        [[nodiscard]] bool HasKeyboardKey(SDL_Scancode compareKey) const;
        [[nodiscard]] bool HasControllerButton(SDL_GameControllerButton compareButton) const;
    };

    // A binding between an Input action and an event
    struct InputBinding final
    {
        template<typename... Args>
        InputBinding(Args&&... args)
        {
            inputEvent.AddListener(std::forward<Args>(args)...);
        }

        InputAction* inputActionPtr{};
        bin::Event<const InputContext&> inputEvent{};

        [[nodiscard]] bool TryExecuteKeyboard(ButtonState buttonState, SDL_Scancode compareKey);
    };

    class Input final : public bin::Singleton<Input>
    {
    public:
        Input() = default;

        Input(Input&& other) = delete;
        Input(const Input& other) = delete;
        Input& operator=(Input&& other) = delete;
        Input& operator=(const Input& other) = delete;

        template<typename ActionName>
        static void AddInputAction(ActionName actionName, const InputAction& inputAction)
        {
            int actionIndex = static_cast<int>(actionName);
            assert(not GetInstance().m_InputActions.contains(actionIndex) && "Input Action Already Bound");

            GetInstance().m_InputActions.emplace(actionIndex, inputAction);
        }

        template<typename ActionName, typename... Args>
        static void Bind(ActionName actionName, Args&&... args)
        {
            int actionIndex = static_cast<int>(actionName);
            assert(GetInstance().m_InputActions.contains(actionIndex) && "Action Does Not Exist");

            auto& bind =
                GetInstance().m_Binds.emplace_back(std::make_unique<InputBinding>(std::forward<Args>(args)...));
            bind->inputActionPtr = &GetInstance().m_InputActions[actionIndex];
        }

        void ProcessInput(bool& shouldQuit);

    private:
        [[nodiscard]] bool HandleKeyboardEvent(const SDL_Event& event);

        std::unordered_map<int, InputAction> m_InputActions{};
        std::vector<std::unique_ptr<InputBinding>> m_Binds{};
    };
}  // namespace bout
#endif  // INPUT_H
