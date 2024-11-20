#include "Sound.h"

#include <SDL_mixer.h>

bin::Sound::Sound(const std::filesystem::path& fullPath) :
    m_MixChunk(Mix_LoadWAV(fullPath.string().c_str()))
{
    if(m_MixChunk == nullptr)
        throw std::runtime_error(std::string("Failed to load sound wave: ") + SDL_GetError());
}

bin::Sound::~Sound() { Mix_FreeChunk(m_MixChunk); }
