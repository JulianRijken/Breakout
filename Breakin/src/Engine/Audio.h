#ifndef AUDIO_H
#define AUDIO_H

#include "Locator.h"
#include "Resources.h"


namespace bin
{
    class Sound;

    // TODO: Audio is handled globally but should ideally work with lifetime and the scene graph
    //       Like a sound node of some sorts
    class Audio final : public Service
    {
    public:
        Audio();
        ~Audio() override;

        Audio(const Audio&) = delete;
        Audio(Audio&&) noexcept = delete;
        Audio& operator=(const Audio&) = delete;
        Audio& operator=(Audio&&) noexcept = delete;

        // Plays resource directly
        static void Play(Sound* sound);

        // Loads from resources
        template<typename SoundName>
        static void Play(SoundName sound)
        {
            Play(Resources::GetSound(sound));
        }

        // 0 to 1
        static void SetGlobalVolume(float volume);

    private:
        float m_GlobalVolume{ 0.5f };
    };
}  // namespace bin

#endif  // AUDIO_H
