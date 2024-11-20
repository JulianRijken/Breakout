#include "Audio.h"

#include <fmt/format.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include <cassert>
#include <stdexcept>

#include "Sound.h"

bin::Audio::Audio()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(fmt::format("SDL_Init Audio Error: {}", SDL_GetError()));

    constexpr int frequency = 44100;
    constexpr Uint16 format = MIX_DEFAULT_FORMAT;
    constexpr int channels = 2;
    constexpr int chunkSize = 2048;

    if(Mix_OpenAudio(frequency, format, channels, chunkSize) < 0)
        throw std::runtime_error(fmt::format("Mix_OpenAudio Error: {}", SDL_GetError()));
}

bin::Audio::~Audio() { Mix_CloseAudio(); }

void bin::Audio::Play(Sound* sound)
{
    assert(sound != nullptr && "Sound is null");

    // TODO: Make voule a global setting
    constexpr int volume = 50;
    Mix_VolumeChunk(sound->m_MixChunk, volume);
    Mix_Volume(-1, volume);
    Mix_PlayChannel(-1, sound->m_MixChunk, 0);
}
