#include "Sprite.h"

#include "Renderer.h"

bin::Sprite::Sprite(const SDL_Color& color) :
    m_Color(color)
{
}

const SDL_Color& bin::Sprite::GetColor() const { return m_Color; }

void bin::Sprite::SetColor(const SDL_Color& color) { m_Color = color; }

void bin::Sprite::Draw(const Renderer& renderer)
{
    renderer.DrawRectRotated(GetWorldPosition(), GetWorldScale(), m_Pivot, GetWorldAngle(), m_Color);
}
