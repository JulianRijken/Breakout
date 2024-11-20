#include "TweenEngine.h"

#include <iostream>

#include "Node.h"

void bin::TweenEngine::Update()
{
    // Loops over all tween instances
    // Erases if decommissioned
    // Keeps track of original size in case of teens starting during the loop
    size_t originalSize = GetInstance().m_TweenInstances.size();
    for(size_t index = 0; index < originalSize;)
    {
        const auto& tweenInstance = GetInstance().m_TweenInstances[index];

        if(tweenInstance->IsDecommissioned())
        {
            GetInstance().m_TweenInstances.erase(GetInstance().m_TweenInstances.begin() + index);
            --originalSize;
        }
        else
        {
            tweenInstance->Update();
            ++index;
        }
    }
}

void bin::TweenEngine::Start(Tween&& tween, Node& target)
{
    if(target.IsGettingDestroyed())
    {
        // We don't crash but simply call the code directly
        std::cerr << "Tween started on getting destroyed object" << std::endl;
        if(tween.invokeWhenDestroyed and tween.onEnd)
            tween.onEnd();

        return;
    }

    // Instantly stop with 0 time
    // In scenarios where the user might input a variable time
    if(tween.delay + tween.duration <= 0)
    {
        if(tween.onEnd)
            tween.onEnd();

        return;
    }

    // Using new instead of make_unique so the constructor can stay private
    GetInstance().m_TweenInstances.emplace_back(
        std::unique_ptr<TweenInstance>(new TweenInstance(std::move(tween), target)));
}

void bin::TweenEngine::Start(const Tween& tween, Node& target)
{
    Tween tweenCopy = tween;
    Start(std::move(tweenCopy), target);
}
