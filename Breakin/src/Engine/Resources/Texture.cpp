#include "Texture.h"

#include <SDL.h>

bin::Texture::Texture(SDL_Texture* texture) :
    m_Texture(texture)
{}

bin::Texture::~Texture() { SDL_DestroyTexture(m_Texture); }

glm::ivec2 bin::Texture::GetSize() const
{
    SDL_Rect dst{};
    SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
    return { dst.w, dst.h };
}

SDL_Texture* bin::Texture::GetSDLTexture() const { return m_Texture; }
