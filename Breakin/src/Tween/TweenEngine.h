#ifndef TWEENENGINE_H
#define TWEENENGINE_H

#include <memory>
#include <vector>

#include "Singleton.h"
#include "Tween.h"
#include "TweenInstance.h"

// Hevaly inspried by "unity-tweens" from Jeffery Lanters
// https://github.com/jeffreylanters/unity-tweens

namespace bin
{
    class Node;

    class TweenEngine final : public bin::Singleton<TweenEngine>
    {
        friend class Core;

    public:
        static void Start(Tween&& tween, Node& target);
        static void Start(const Tween& tween, Node& target);

    private:
        static void Update();
        std::vector<std::unique_ptr<TweenInstance>> m_TweenInstances;
    };

}  // namespace bin
#endif // TWEENENGINE_H
