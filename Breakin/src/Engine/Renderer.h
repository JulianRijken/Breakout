#ifndef RENDERER_H
#define RENDERER_H

#include <SDL_pixels.h>

#include <glm/vec2.hpp>

#include "Locator.h"

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Surface;
struct SDL_Texture;

namespace bin
{

    class Texture;

    class Renderer final : public bin::Service
    {
        friend class Core;

    public:
        explicit Renderer(SDL_Window* windowPtr);

        void DrawLine(const glm::vec2& from, const glm::vec2& to,
                      const SDL_Color& color = { 255, 255, 255, 255 }) const;

        void DrawTexture(const Texture* texture, const glm::vec2& position, float pixelsPerUnit,
                         const glm::vec2& pivot) const;

        void DrawBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot = { 0.5, 0.5 },
                     const SDL_Color& color = { 255, 255, 255, 255 }) const;

        void DrawWireBox(const glm::vec2& position, const glm::vec2& scale, const glm::vec2& pivot = { 0.5, 0.5 },
                         const SDL_Color& color = { 255, 255, 255, 255 }) const;

        [[nodiscard]] static glm::ivec2 GetWindowSize();
        [[nodiscard]] static float GetAspectRatio();

        [[nodiscard]] static glm::ivec2 GetWindowSizeClamped();
        [[nodiscard]] static float GetAspectRatioClamped();

        [[nodiscard]] static SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

    private:
        void Render() const;
        void DrawUnitGrid() const;

        SDL_Renderer* m_RendererPtr{};
        SDL_Window* m_WindowPtr{};
    };
}  // namespace bin
#endif  // RENDERER_H
