#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_pixels.h>

#include "Node.h"

namespace bin
{
    class Sprite final : public Node
    {
    public:
        Sprite(const SDL_Color& color = { 255, 255, 255, 255 });

        [[nodiscard]] const SDL_Color& GetColor() const;
        void SetColor(const SDL_Color& color);

    private:
        void Draw(const Renderer& renderer) override;

        glm::vec2 m_Pivot{ 0.5f, 0.5f };
        SDL_Color m_Color{ 255, 255, 255, 255 };
    };
}  // namespace bin

#endif  // SPRITE_H
