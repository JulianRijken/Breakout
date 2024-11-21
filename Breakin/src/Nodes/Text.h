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
        Text(std::string text, Font* font, const glm::vec2& alignment = { 0.5f, 0.5f }, float size = 1.0f,
             SDL_Color color = { 255, 255, 255, 255 });

        ~Text() override = default;
        Text(Text&&) = delete;
        Text(const Text&) = delete;
        Text& operator=(Text&&) = delete;
        Text& operator=(const Text&) = delete;

        [[nodiscard]] float GetSize() const;

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
