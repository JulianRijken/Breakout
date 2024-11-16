#ifndef RENDERER_H
#define RENDERER_H


#include <SDL_pixels.h>

#include <glm/vec2.hpp>

#include "Locator.h"

struct SDL_Renderer;
struct SDL_Window;

namespace jul
{
    class Renderer final : public jul::Service
    {
    public:
        Renderer(SDL_Window* windowPtr);

        void Render();

        void SetClearColor(const SDL_Color& color);
        void DrawLine(const glm::vec2& from, const glm::vec2& to, const SDL_Color& color = { 255, 255, 255, 255 });

        void DrawBox(const glm::vec2& position, const glm::vec2& scale,
                     const SDL_Color& color = { 255, 255, 255, 255 });

        void DrawWireBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot = { 0.5, 0.5 },
                         const SDL_Color& color = { 255, 255, 255, 255 });

        [[nodiscard]] glm::ivec2 GetWindowSize();
        [[nodiscard]] float GetAspectRatio();
        [[nodiscard]] glm::ivec2 WorldToScreenScale(const glm::vec2& worldScale);
        [[nodiscard]] glm::ivec2 WorldToScreenPosition(const glm::vec2& worldPosition);
        [[nodiscard]] glm::vec2 ScreenToWorldPosition(const glm::ivec2& screenPosition);

    private:
        float m_OrthoSize = 10;  // Should be in camera

        SDL_Renderer* m_RendererPtr{};
        SDL_Window* m_WindowPtr{};
        SDL_Color m_ClearColor{ 25, 25, 25, 0 };
    };
}  // namespace jul
#endif  // RENDERER_H
