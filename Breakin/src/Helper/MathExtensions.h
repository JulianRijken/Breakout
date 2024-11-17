#ifndef MATHEXTENSIONS_H
#define MATHEXTENSIONS_H

#include <SDL_pixels.h>

#include <algorithm>
#include <glm/exponential.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <numbers>

namespace bin::math
{
    // TODO: For the random stuff consider std::rand or random number generator
    //       this also to make it thread safe
    template<typename Type = float>
        requires std::floating_point<Type>
    constexpr Type RandomValue()
    {
        return static_cast<Type>(rand() % RAND_MAX) / static_cast<Type>(RAND_MAX);
    };

    template<typename Type>
        requires std::floating_point<Type>
    constexpr Type RandomRange(Type min, Type max)
    {
        if (min > max)
        {
            const Type tempMax = max;
            max = min;
            min = tempMax;
        }

        const Type randomAlpha{ Type(rand()) / RAND_MAX };
        const Type range{ max - min };

        return randomAlpha * range + min;
    }

    template<typename Type>
        requires std::integral<Type>
    constexpr Type RandomRange(Type min, Type max)
    {
        if (min > max)
        {
            Type tempMax = max;
            max = min;
            min = tempMax;
        }

        return rand() % (max - min + 1) + min;
    }

    template<typename Type>
    constexpr const Type& Clamp01(const Type& value)
    {
        return std::clamp(value, static_cast<Type>(0), static_cast<Type>(1));
    };

    template<typename Type>
        requires std::integral<Type> or std::floating_point<Type>
    constexpr Type ClampLoop(Type value, Type min, Type max)
    {
        if(min == max)
            return value;

        if (min > max)
        {
            const Type tempMax = max;
            max = min;
            min = tempMax;
        }

        Type range = max - min;

        while(value > max)
        {
            Type offset = value - max;
            value -= range + offset;
        }

        while(value < min)
        {
            Type offset = min - value;
            value += range + offset;
        }

        return value;
    }

    template<typename Type>
        requires std::integral<Type> or std::floating_point<Type>
    constexpr Type ClampLoop01(Type value)
    {
        return ClampLoop(value, static_cast<Type>(0), static_cast<Type>(1));
    };

    template<typename Type, typename TimeType>
    Type Lerp(const Type& a, const Type& b, TimeType t)
    {
        return std::lerp(a, b, t);
    }

    template<typename TimeType>
    SDL_Color Lerp(const SDL_Color& a, const SDL_Color& b, TimeType t)
    {
        return { static_cast<Uint8>(std::lerp(a.r, b.r, t)),
                 static_cast<Uint8>(std::lerp(a.g, b.g, t)),
                 static_cast<Uint8>(std::lerp(a.b, b.b, t)),
                 static_cast<Uint8>(std::lerp(a.a, b.a, t)) };
    }

    template<typename Type>
    Type LerpSmooth(const Type& a, const Type& b, double duration, double deltaTime)
    {
        const double h{ -duration / glm::log2(1.0 / 100.0) };

        return glm::mix(b, a, glm::exp2(-deltaTime / h));
    }

    template<typename Type, typename DeltaType>
        requires std::integral<Type> or std::floating_point<Type>
    Type MoveTowards(const Type& a, const Type& b, DeltaType maxDelta)
    {
        if(std::fabs(b - a) <= maxDelta)
            return b;

        return a + std::copysign(maxDelta, b - a);
    }

    template<typename Type>
        requires std::floating_point<Type>
    constexpr Type MapWave(const Type time, const Type min, const Type max, const Type repeatTime, const Type startTime)
    {
        const Type amplitude{ (max - min) / 2.0f };
        const Type intercept{ min + amplitude };
        const Type pulsation{ 2 * std::numbers::pi_v<Type> / repeatTime };
        const Type phase{ 2 * std::numbers::pi_v<Type> * startTime };

        return amplitude * std::sin(pulsation * time + phase) + intercept;
    }

    template<typename Type>
        requires std::floating_point<Type>
    constexpr Type MapValueInRange(Type value, Type inRangeMin, Type inRangeMax, Type outRangeMin = 0.0,
                                   Type outRangeMax = 1.0)
    {
        return (value - inRangeMin) * (outRangeMax - outRangeMin) / (inRangeMax - inRangeMin) + outRangeMin;
    }

    template<typename Type>
        requires std::floating_point<Type>
    constexpr Type MapValueInRangeClamped(Type value, Type inRangeMin, Type inRangeMax, Type outRangeMin = 0.0,
                                          Type outRangeMax = 1.0)
    {
        return std::clamp((value - inRangeMin) * (outRangeMax - outRangeMin) / (inRangeMax - inRangeMin) + outRangeMin,
                          outRangeMin,
                          outRangeMax);
    }
}
#endif // MATHEXTENSIONS_H
