#ifndef AUDIO_H
#define AUDIO_H

#include "Locator.h"

namespace bin
{
    class Sound;

    // TODO: Audio is handled globally but should ideally work with lifetime and the scene graph
    class Audio final : public bin::Service
    {
    public:
        Audio();
        ~Audio() override;

        Audio(const Audio&) = delete;
        Audio(Audio&&) noexcept = delete;
        Audio& operator=(const Audio&) = delete;
        Audio& operator=(Audio&&) noexcept = delete;

        static void Play(Sound* sound);
    };
}  // namespace bin

#endif  // AUDIO_H
