#include "EaseFunction.h"

#include <cmath>
#include <glm/ext/scalar_constants.hpp>

float bin::easeFunction::Linear(float time) { return time; }

float bin::easeFunction::SineIn(float time) { return 1.0f - std::cos(time * glm::pi<float>() / 2.0f); }

float bin::easeFunction::SineOut(float time) { return std::sin(time * glm::pi<float>() / 2.0f); }

float bin::easeFunction::SineInOut(float time) { return -(std::cos(glm::pi<float>() * time) - 1.0f) / 2.0f; }

float bin::easeFunction::BounceOut(float time)
{
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
    return time < 0.5f ? (1 - BounceOut(1 - 2 * time)) / 2 : (1 + BounceOut(2 * time - 1)) / 2;
}

float bin::easeFunction::BounceInLerp(float time) { return 1 - BounceOut(1 - time); }

float bin::easeFunction::ElasticIn(float time)
{
    return time == 0.0f ? 0.0f
         : time == 1.0f ? 1.0f
                        : -std::pow(2.0f, 10.0f * time - 10.0f) * std::sin((time * 10.0f - 10.75f) * CONSTANT_D);
}

float bin::easeFunction::ElasticOut(float time)
{
    return time == 0.0f ? 0.0f
         : time == 1.0f ? 1.0f
                        : std::pow(2.0f, -10.0f * time) * std::sin((time * 10 - 0.75f) * CONSTANT_D) + 1.0f;
}

float bin::easeFunction::ElasticInOut(float time)
{
    return time == 0.0f ? 0.0f
         : time == 1.0f ? 1.0f
         : time < 0.5f
             ? -(std::pow(2.0f, 20.0f * time - 10.0f) * std::sin((20.0f * time - 11.125f) * CONSTANT_E)) / 2.0f
             : std::pow(2.0f, -20.0f * time + 10.0f) * std::sin((20.0f * time - 11.125f) * CONSTANT_E) / 2.0f + 1.0f;
}


float bin::easeFunction::Evaluate(float time, EaseType type)
{
    switch(type)
    {
        case EaseType::Linear:
            return Linear(time);
        case EaseType::SineIn:
            return SineIn(time);
        case EaseType::SineOut:
            return SineOut(time);
        case EaseType::SineInOut:
            return SineInOut(time);
        case EaseType::BounceIn:
            return BounceInLerp(time);
        case EaseType::BounceOut:
            return BounceOut(time);
        case EaseType::BounceInOut:
            return BounceInOutLerp(time);
        case EaseType::ElasticIn:
            return ElasticIn(time);
        case EaseType::ElasticInOut:
            return ElasticInOut(time);
        case EaseType::ElasticOut:
            return ElasticOut(time);
    }

    return 0.0f;
}
