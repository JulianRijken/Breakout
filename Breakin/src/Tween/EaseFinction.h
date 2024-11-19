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
        double LinearLerp(double time);

        double SineInLerp(double time);

        double SineOutLerp(double time);

        double SineInOutLerp(double time);

        double BounceOutLerp(double time);

        double BounceInLerp(double time);

        double BounceInOutLerp(double time);

        double Evaluate(double time, EaseType type);
    }  // namespace easeFunction

}  // namespace bin
#endif  // EASEFINCTION_H
