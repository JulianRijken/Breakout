#ifndef INPUT_H
#define INPUT_H

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
        // Like passing the value of a gameplay trigger
        ButtonState state;
    };

    // The action linking separating the action and the keys
    struct InputAction final
    {
        std::vector<SDL_Scancode> keyboardButtons{};
        bool leftMouseButton{};
        bool rightMouseButton{};

        [[nodiscard]] bool HasKeyboardKey(SDL_Scancode compareKey) const;
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
        Event<const InputContext&> inputEvent{};
    };

    class Input final : public Singleton<Input>
    {
        friend class Core;

    public:
        Input() = default;
        ~Input() override = default;

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
            const int actionIndex = static_cast<int>(actionName);
            assert(GetInstance().m_InputActions.contains(actionIndex) && "Action Does Not Exist");

            auto& bind =
                GetInstance().m_Binds.emplace_back(std::make_unique<InputBinding>(std::forward<Args>(args)...));
            bind->inputActionPtr = &GetInstance().m_InputActions[actionIndex];
        }

        static glm::ivec2 GetMousePosition();
        static Uint32 GetMouseState();

    private:
        void ProcessInput(bool& shouldQuit) const;

        std::unordered_map<int, InputAction> m_InputActions{};
        std::vector<std::unique_ptr<InputBinding>> m_Binds{};
    };
}  // namespace bout
#endif  // INPUT_H
