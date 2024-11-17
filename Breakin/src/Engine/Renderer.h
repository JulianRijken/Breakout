#ifndef RENDERER_H
#define RENDERER_H

#include <SDL_pixels.h>

#include <glm/vec2.hpp>

#include "Locator.h"

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Surface;

namespace bin
{

    class Texture;

    class Renderer final : public bin::Service
    {
    public:
        explicit Renderer(SDL_Window* windowPtr);

        void Render() const;

        void SetClearColor(const SDL_Color& color);
        void DrawLine(const glm::vec2& from, const glm::vec2& to, const SDL_Color& color = { 255, 255, 255, 255 }) const;

        void DrawTexture(Texture* texture, const glm::vec2& position, float pixelsPerUnit,
                         const glm::vec2& pivot) const;

        void DrawBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot = { 0.5, 0.5 },
                     const SDL_Color& color = { 255, 255, 255, 255 }) const;

        void DrawWireBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot = { 0.5, 0.5 },
                         const SDL_Color& color = { 255, 255, 255, 255 }) const;

        [[nodiscard]] static glm::ivec2 GetWindowSize();
        [[nodiscard]] static float GetAspectRatio();

        [[nodiscard]] static glm::ivec2 GetWindowSizeClamped();
        [[nodiscard]] static float GetAspectRatioClamped();


        [[nodiscard]] SDL_Renderer* GetSDLRenderer();


    private:
        void DrawUnitGrid() const;

        SDL_Renderer* m_RendererPtr{};
        SDL_Window* m_WindowPtr{};
        SDL_Color m_ClearColor{ 25, 25, 25, 0 };
    };
}  // namespace bin
#endif  // RENDERER_H
