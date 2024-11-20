#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Font.h"
#include "Node.h"
#include "Texture.h"

namespace bin
{
    class Text final : public Node
    {
    public:
        Text(std::string text, Font* font, const glm::vec2& alignment = { 0, 0 }, float size = 1.0f,
             SDL_Color color = { 255, 255, 255, 255 });

        [[nodiscard]] float GetSize();

        void SetText(const std::string& text);
        void SetSize(float size);
        void SetColor(const SDL_Color& color);

    private:
        void UpdateTextTexture();
        void Draw(const Renderer& renderer) override;

        SDL_Color m_Color{ 255, 255, 255, 255 };
        std::string m_Text{};
        glm::vec2 m_Alignment{};
        float m_Size{ 1.0f };

        Font* m_FontPtr{};
        std::unique_ptr<Texture> m_TexturePtr{};
    };
}  // namespace bin
#endif  // TEXT_H
