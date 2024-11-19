#include "Text.h"

#include "Renderer.h"
#include "Texture.h"

bin::Text::Text(std::string text, Font* font, const glm::vec2& alignment, float size, SDL_Color color) :
    m_Color(color),
    m_Text(std::move(text)),
    m_Alignment(alignment),
    m_Size(size),
    m_FontPtr(font)
{
    UpdateTextTexture();
}

void bin::Text::SetText(const std::string& text)
{
    if(m_Text == text)
        return;

    m_Text = text;
    UpdateTextTexture();
}

void bin::Text::UpdateTextTexture()
{
    if(m_Text.empty())
    {
        m_TexturePtr = nullptr;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(m_FontPtr->GetFont(), m_Text.c_str(), m_Color);
    if(surface == nullptr)
        throw std::runtime_error(std::string("Failed to create surface: ") + SDL_GetError());

    auto* texture = Renderer::CreateTextureFromSurface(surface);
    SDL_FreeSurface(surface);

    if(texture == nullptr)
        throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

    m_TexturePtr = std::make_unique<bin::Texture>(texture);
}

void bin::Text::Draw(const Renderer& renderer)
{
    if(m_Text.empty())
        m_TexturePtr = nullptr;

    if(m_TexturePtr == nullptr)
        return;

    renderer.DrawTexture(
        m_TexturePtr.get(), GetWorldPosition(), static_cast<float>(m_FontPtr->GetSize()) / m_Size, m_Alignment);
}
