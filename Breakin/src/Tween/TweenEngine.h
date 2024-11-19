#ifndef TWEENENGINE_H
#define TWEENENGINE_H

#include <functional>
#include <memory>
#include <vector>

#include "EaseFinction.h"
#include "Singleton.h"

namespace bin
{
    class TweenInstance;
    class Node;

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

    class TweenEngine final : public bin::Singleton<TweenEngine>
    {
        friend class Core;

    public:
        static void Start(Tween&& tween, Node& target);
        static void Start(const Tween& tween, Node& target);

    private:
        static void Update();
        std::vector<std::unique_ptr<TweenInstance>> m_TweenInstances{};
    };

}  // namespace jul
#endif // TWEENENGINE_H
