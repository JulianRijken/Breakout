#ifndef EASEFINCTION_H
#define EASEFINCTION_H

// Ease functions based on ease functions form "unity-tweens" by Jeffery Lanters
// https://github.com/jeffreylanters/unity-tweens/blob/master/Runtime/Core/EaseFunctions.cs

#include <glm/ext/scalar_constants.hpp>

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
        BounceInOut,
        ElasticIn,
        ElasticOut,
        ElasticInOut
    };

    namespace easeFunction
    {
        static constexpr float CONSTANT_F = 7.5625f;
        static constexpr float CONSTANT_G = 2.75f;
        static constexpr float CONSTANT_D = 2.0f * glm::pi<float>() / 3.0f;
        static constexpr float CONSTANT_E = 2.0f * glm::pi<float>() / 4.5f;

        float Linear(float time);

        float SineIn(float time);

        float SineOut(float time);

        float SineInOut(float time);

        float BounceOut(float time);

        float BounceInLerp(float time);

        float BounceInOutLerp(float time);

        float ElasticIn(float time);

        float ElasticOut(float time);

        float ElasticInOut(float time);


        float Evaluate(float time, EaseType type);
    }  // namespace easeFunction

}  // namespace bin
#endif  // EASEFINCTION_H
