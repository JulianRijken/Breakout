#ifndef TWEENENGINE_H
#define TWEENENGINE_H

#include <memory>
#include <vector>

#include "Singleton.h"

namespace bin
{
    class TweenInstance;
    struct Tween;
    class Node;

    class TweenEngine final : public bin::Singleton<TweenEngine>
    {
        friend class Core;

    public:
        static void Start(Tween&& tween, Node& target);
        static void Start(const Tween& tween, Node& target);

    private:
        void Update();
        std::vector<std::unique_ptr<TweenInstance>> m_TweenInstances{};
    };

}  // namespace jul
#endif // TWEENENGINE_H
