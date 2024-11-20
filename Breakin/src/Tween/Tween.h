#ifndef TWEEN_H
#define TWEEN_H

#include <functional>

#include "EaseFinction.h"

namespace bin
{
    struct Tween final
    {
        float delay = 0.0;
        float from = 0.0;
        float to = 1.0;
        float duration = 1.0;
        bool igunoreTimeScale = false;
        bool invokeWhenDestroyed = false;
        EaseType easeType = EaseType::Linear;

        std::function<void()> onStart = {};
        std::function<void(float)> onUpdate = {};
        std::function<void()> onEnd = {};
    };
}  // namespace bin

#endif  // TWEEN_H
