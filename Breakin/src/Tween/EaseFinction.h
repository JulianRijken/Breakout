#ifndef EASEFINCTION_H
#define EASEFINCTION_H

namespace bin
{
    enum class EaseType
    {
        Linear,
        SineIn,
        SineOut,
        SineInOut,
        BounceIn,
        BounceOut,
        BounceInOut
    };

    namespace easeFunction
    {
        float LinearLerp(float time);

        float SineInLerp(float time);

        float SineOutLerp(float time);

        float SineInOutLerp(float time);

        float BounceOutLerp(float time);

        float BounceInLerp(float time);

        float BounceInOutLerp(float time);

        float Evaluate(float time, EaseType type);
    }  // namespace easeFunction

}  // namespace bin
#endif  // EASEFINCTION_H
