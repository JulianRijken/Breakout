#ifndef RENDERER_H
#define RENDERER_H

#include <SDL_pixels.h>
#include <glm/vec2.hpp>
#include "Locator.h"

struct SDL_Renderer;
struct SDL_Window;

namespace bin
{
    class Renderer final : public bin::Service
    {
    public:
        Renderer(SDL_Window* windowPtr);

        void Render();

        void SetClearColor(const SDL_Color& color);
        void DrawLine(const glm::vec2& from, const glm::vec2& to, const SDL_Color& color = { 255, 255, 255, 255 });

        void DrawBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot,
                     const SDL_Color& color = { 255, 255, 255, 255 });

        void DrawWireBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot = { 0.5, 0.5 },
                         const SDL_Color& color = { 255, 255, 255, 255 });

        [[nodiscard]] glm::ivec2 GetWindowSize() const;
        [[nodiscard]] float GetAspectRatio() const;


    private:
        SDL_Renderer* m_RendererPtr{};
        SDL_Window* m_WindowPtr{};
        SDL_Color m_ClearColor{ 25, 25, 25, 0 };
    };
}  // namespace bin
#endif  // RENDERER_H
