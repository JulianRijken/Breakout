#include "EaseFinction.h"

#include <cmath>
#include <glm/ext/scalar_constants.hpp>

float bin::easeFunction::LinearLerp(float time) { return time; }

float bin::easeFunction::SineInLerp(float time) { return 1.0f - std::cos(time * glm::pi<float>() / 2.0f); }

float bin::easeFunction::SineOutLerp(float time) { return std::sin(time * glm::pi<float>() / 2.0f); }

float bin::easeFunction::SineInOutLerp(float time) { return -(std::cos(glm::pi<float>() * time) - 1.0f) / 2.0f; }

float bin::easeFunction::BounceOutLerp(float time)
{
    // TODO: Get rid of the magic numbers
    static constexpr float CONSTANT_F = 7.5625f;
    static constexpr float CONSTANT_G = 2.75f;

    if(time < 1.0f / CONSTANT_G)
        return CONSTANT_F * time * time;

    if(time < 2.0f / CONSTANT_G)
    {
        time -= 1.5f / CONSTANT_G;
        return CONSTANT_F * time * time + 0.75f;
    }

    if(time < 2.5f / CONSTANT_G)
    {
        time -= 2.25f / CONSTANT_G;
        return CONSTANT_F * time * time + 0.9375f;
    }

    time -= 2.625f / CONSTANT_G;
    return CONSTANT_F * time * time + 0.984375f;
}

float bin::easeFunction::BounceInOutLerp(float time)
{
    return time < 0.5f ? (1 - BounceOutLerp(1 - 2 * time)) / 2 : (1 + BounceOutLerp(2 * time - 1)) / 2;
}

float bin::easeFunction::Evaluate(float time, EaseType type)
{
    switch(type)
    {
        case EaseType::Linear:
            return LinearLerp(time);
        case EaseType::SineIn:
            return SineInLerp(time);
        case EaseType::SineOut:
            return SineOutLerp(time);
        case EaseType::SineInOut:
            return SineInOutLerp(time);
        case EaseType::BounceIn:
            return BounceInLerp(time);
        case EaseType::BounceOut:
            return BounceOutLerp(time);
        case EaseType::BounceInOut:
            return BounceInOutLerp(time);
    }

    return 0.0f;
}

float bin::easeFunction::BounceInLerp(float time) { return 1 - BounceOutLerp(1 - time); }
