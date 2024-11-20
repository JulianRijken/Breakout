#ifndef AUDIO_H
#define AUDIO_H

namespace bin
{
    // TODO: Audio is handled globally but should ideally work with lifetime and the scene graph
    class Audio final
    {
    public:
        Audio();
        ~Audio();

    private:
        void Play();
    };
}  // namespace bin

#endif  // AUDIO_H
