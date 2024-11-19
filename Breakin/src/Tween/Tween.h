#ifndef TWEEN_H
#define TWEEN_H

#include <functional>

#include "EaseFinction.h"

namespace bin
{
    struct Tween
    {
        double delay = 0.0;
        double from = 0.0;
        double to = 1.0;
        double duration = 1.0;
        bool igunoreTimeScale = false;
        bool invokeWhenDestroyed = false;
        EaseType easeType = EaseType::Linear;

        std::function<void()> onStart = {};
        std::function<void(double)> onUpdate = {};
        std::function<void()> onEnd = {};
    };
}  // namespace jul
#endif // TWEEN_H
