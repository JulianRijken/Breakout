#include "EaseFinction.h"

#include <cmath>
#include <numbers>

double bin::easeFunction::LinearLerp(double time) { return time; }

double bin::easeFunction::SineInLerp(double time) { return 1.0 - std::cos((time * std::numbers::pi) / 2.0); }

double bin::easeFunction::SineOutLerp(double time) { return std::sin((time * std::numbers::pi) / 2.0f); }

double bin::easeFunction::SineInOutLerp(double time) { return -(std::cos(std::numbers::pi * time) - 1.0f) / 2.0f; }

double bin::easeFunction::BounceOutLerp(double time)
{
    // TODO: Get rid of the magic numbers
    static constexpr float CONSTANT_F = 7.5625;
    static constexpr float CONSTANT_G = 2.75;

    if(time < 1 / CONSTANT_G)
        return CONSTANT_F * time * time;

    if(time < 2 / CONSTANT_G)
    {
        time -= 1.5 / CONSTANT_G;
        return CONSTANT_F * time * time + 0.75;
    }

    if(time < 2.5 / CONSTANT_G)
    {
        time -= 2.25 / CONSTANT_G;
        return CONSTANT_F * time * time + 0.9375;
    }

    time -= 2.625 / CONSTANT_G;
    return CONSTANT_F * time * time + 0.984375;
}

double bin::easeFunction::BounceInOutLerp(double time)
{
    return time < 0.5 ? (1 - BounceOutLerp(1 - 2 * time)) / 2 : (1 + BounceOutLerp(2 * time - 1)) / 2;
}

double bin::easeFunction::Evaluate(double time, EaseType type)
{
    switch(type)
    {
        case EaseType::Linear:
            return LinearLerp(time);
            break;
        case EaseType::SineIn:
            return SineInLerp(time);
            break;
        case EaseType::SineOut:
            return SineOutLerp(time);
            break;
        case EaseType::SineInOut:
            return SineInOutLerp(time);
            break;
        case EaseType::BounceIn:
            return BounceInLerp(time);
            break;
        case EaseType::BounceOut:
            return BounceOutLerp(time);
            break;
        case EaseType::BounceInOut:
            return BounceInOutLerp(time);
            break;
    }

    return 0.0;
}

double bin::easeFunction::BounceInLerp(double time) { return 1 - BounceOutLerp(1 - time); }
