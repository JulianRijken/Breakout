#include "Font.h"

#include <SDL_ttf.h>

#include <stdexcept>

TTF_Font* bin::Font::GetFont() const { return m_Font; }

bin::Font::Font(const std::filesystem::path& fullPath, int size) :
    m_Size(size),
    m_Font(TTF_OpenFont(fullPath.string().c_str(), size))
{
	if (m_Font == nullptr) 
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
}

int bin::Font::GetSize() const { return m_Size; }

bin::Font::~Font() { TTF_CloseFont(m_Font); }
