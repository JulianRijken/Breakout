#include "Text.h"

#include "Renderer.h"
#include "Texture.h"

bin::Text::Text(const std::string& text, Font* font, glm::vec2 alighnment, float size, SDL_Color color) :
    m_Color(color),
    m_Text(text),
    m_Alighnment(alighnment),
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
    SDL_Surface* surface = TTF_RenderText_Solid(m_FontPtr->GetFont(), m_Text.c_str(), m_Color);
    if(surface == nullptr)
        throw std::runtime_error(std::string("Failed to create surface: ") + SDL_GetError());

    auto& renderer = bin::Locator::Get<Renderer>();
    m_TexturePtr = renderer.CreateTextureFromSurface(surface);
    SDL_FreeSurface(surface);
}

void bin::Text::Draw(const Renderer& renderer)
{
    if(m_Text.empty())
        m_TexturePtr = nullptr;

    renderer.DrawTexture(
        m_TexturePtr.get(), GetWorldPosition(), static_cast<float>(m_FontPtr->GetSize()) / m_Size, m_Alighnment);
}
