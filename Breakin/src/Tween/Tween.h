#ifndef TWEEN_H
#define TWEEN_H

#include <functional>
#include "EaseFinction.h"

namespace bin
{
    struct Tween final
    {
        float delay = 0.0f;
        float from = 0.0f;
        float to = 1.0f;
        float duration = 1.0f;
        bool ignoreTimeScale = false;
        bool invokeWhenDestroyed = false;
        EaseType easeType = EaseType::Linear;

        std::function<void()> onStart = {};
        std::function<void(float)> onUpdate = {};
        std::function<void()> onEnd = {};
    };
}  // namespace bin

#endif  // TWEEN_H
