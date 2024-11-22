#ifndef RENDERER_H
#define RENDERER_H

#include <SDL_pixels.h>

#include <glm/vec2.hpp>

#include "Locator.h"
#include "Texture.h"

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Surface;

namespace bin
{
    class Texture;

    class Renderer final : public Service
    {
        friend class Core;

    public:
        explicit Renderer(SDL_Window* windowPtr);

        void DrawLine(const glm::vec2& from, const glm::vec2& to,
                      const SDL_Color& color = { 255, 255, 255, 255 }) const;

        void DrawTexture(const Texture* texturePtr, const glm::vec2& position, const glm::vec2& scale,
                         float pixelsPerUnit, const glm::vec2& pivot) const;

        void DrawRectRotated(const glm::vec2& position, const glm::vec2& scale = { 1.0f, 1.0f },
                             const glm::vec2& pivot = { 0.5f, 0.5f }, float angle = 0.0f,
                             const SDL_Color& color = { 255, 255, 255, 255 }) const;

        void DrawRect(const glm::vec2& position, const glm::vec2& scale = { 1.0f, 1.0f },
                      const glm::vec2& pivot = { 0.5f, 0.5f }, const SDL_Color& color = { 255, 255, 255, 255 }) const;

        void DrawWireRect(const glm::vec2& position, const glm::vec2& scale = { 1.0f, 1.0f },
                          const glm::vec2& pivot = { 0.5f, 0.5f },
                          const SDL_Color& color = { 255, 255, 255, 255 }) const;

        [[nodiscard]] static glm::ivec2 GetWindowSize();
        [[nodiscard]] static float GetAspectRatio();

        [[nodiscard]] static SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

    private:
        void Render() const;
        void DrawUnitGrid() const;

        SDL_Renderer* m_RendererPtr{};
        SDL_Window* m_WindowPtr{};
        std::unique_ptr<Texture> m_EmptyTexture{};
    };
}  // namespace bin
#endif  // RENDERER_H
