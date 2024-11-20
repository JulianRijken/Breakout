#ifndef BUTTON_H
#define BUTTON_H

#include <SDL_pixels.h>

#include <glm/vec2.hpp>

#include "Event.h"
#include "Node.h"

namespace bin
{
    class Button final : public Node
    {
    public:
        Button(const glm::vec2& size);
        ~Button() override = default;

        Button(Button&&) = delete;
        Button(const Button&) = delete;
        Button& operator=(Button&&) = delete;
        Button& operator=(const Button&) = delete;

        bin::Event<> m_OnPress{};
        bin::Event<> m_OnReleased{};

        float m_SelectedScale{ 1.2f };                    // NOLINT - C.131: Avoid trivial getters and setters
        float m_ScaleLerpDuration{ 0.2f };                // NOLINT - C.131: Avoid trivial getters and setters
        SDL_Color m_IdleColor{ 200, 200, 200, 255 };      // NOLINT - C.131: Avoid trivial getters and setters
        SDL_Color m_SelectedColor{ 255, 255, 255, 255 };  // NOLINT - C.131: Avoid trivial getters and setters
        SDL_Color m_PressedColor{ 150, 150, 255, 255 };   // NOLINT - C.131: Avoid trivial getters and setters

    private:
        void Update() override;
        void Draw(const Renderer& renderer) override;

        void OnPress();
        void OnReleased();


        bool m_IsMouseOver{};
        bool m_IsMouseDown{};

        float m_CurrentScale{};

        bool m_IsPressed{};
        SDL_Color m_Color{ 255, 255, 255, 255 };
        glm::vec2 m_Size{};
    };
}  // namespace bin

#endif  // BUTTON_H
