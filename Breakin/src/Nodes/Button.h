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

    private:
        void Update() override;
        void Draw(const Renderer& renderer) override;

        void OnPress();
        void OnReleased();

        static constexpr float SELECTED_SCALE{ 1.2f };
        static constexpr float SCALE_LERP_DURATION{ 0.2f };


        bool m_IsSelected{};
        bool m_IsDown{};

        float m_CurrentScale{};

        bool m_IsPressed{};
        SDL_Color m_Color{ 255, 255, 255, 255 };
        glm::vec2 m_Size{};
    };
}  // namespace bin

#endif  // BUTTON_H
