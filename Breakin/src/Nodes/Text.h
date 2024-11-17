#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Font.h"
#include "Node.h"

namespace bin
{
    class Texture;

    class Text final : public Node
    {
    public:
        Text(const std::string& text, Font* font, glm::vec2 alighnment = { 0, 0 },
             SDL_Color color = { 255, 255, 255, 255 });

        void SetText(const std::string& text);

    private:
        void UpdateTextTexture();
        void Draw(const Renderer& renderer) override;

        SDL_Color m_Color{ 255, 255, 255, 255 };
        std::string m_Text{};
        glm::vec2 m_Alighnment{};
        glm::vec2 m_Size{};

        Font* m_FontPtr{};
        std::unique_ptr<Texture> m_TexturePtr{};
    };
}  // namespace bin
#endif  // TEXT_H
