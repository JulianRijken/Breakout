#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

#include <filesystem>

namespace bin
{
    // Simple RAII wrapper for Mix_Chunk
    class Sound final
    {
        friend class Audio;

    public:
        explicit Sound(const std::filesystem::path& fullPath);
        ~Sound();

        Sound(Sound&&) = delete;
        Sound(const Sound&) = delete;
        Sound& operator=(Sound&&) = delete;
        Sound& operator=(const Sound&) = delete;

    private:
        Mix_Chunk* m_MixChunk;
    };
}  // namespace bin
#endif  // SOUND_H
