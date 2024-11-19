#include "TweenInstance.h"

#include <cmath>

#include "GameTime.h"
#include "MathExtensions.h"
#include "Node.h"
#include "Tween.h"

bin::TweenInstance::TweenInstance(Tween&& tween, Node& target) :
    m_IsHalting(tween.delay > 0),
    m_Target(&target),
    m_Tween(std::move(tween))
{
    // Sets target to nullptr when detroyed
    m_Target->m_OnDestroyedEvent.AddListener(this, &TweenInstance::OnTargetDestroyed);
}

void bin::TweenInstance::OnTargetDestroyed(Node& /*unused*/) { m_Target = nullptr; }

void bin::TweenInstance::Cancel()
{
    if(m_Tween.invokeWhenDestroyed and m_Target == nullptr)
    {
        if(m_Tween.onEnd)
            m_Tween.onEnd();
    }

    m_IsDecommissioned = true;
}

void bin::TweenInstance::Update()
{
    if(m_Target == nullptr)
    {
        Cancel();
        return;
    }

    const float deltaTime = m_Tween.igunoreTimeScale ? GameTime::GetUnscaledDeltaTime() : GameTime::GetDeltaTime();

    if(m_IsHalting)
    {
        m_Tween.delay -= deltaTime;
        if(m_Tween.delay > 0)
            return;

        // Compensate for overshot;
        m_Tween.duration += m_Tween.delay;

        m_IsHalting = false;
    }

    if(m_Tween.onStart)
    {
        m_Tween.onStart();
        m_Tween.onStart = {};  // Remove start function as soon as called
    }

    m_Time += deltaTime;

    // Yes, deltatime can go below 0
    // when we change time scale :)
    m_Time = std::max(0.0f, m_Time);

    if(m_Time >= m_Tween.duration)
    {
        m_Time = m_Tween.duration;
        m_HasReachedEnd = true;
    }


    const float alpha = bin::math::Clamp01(m_Time / m_Tween.duration);
    const float easedTime = easeFunction::Evaluate(alpha, m_Tween.easeType);
    const float interpolatedValue = std::lerp(m_Tween.from, m_Tween.to, easedTime);


    if(m_Tween.onUpdate)
        m_Tween.onUpdate(interpolatedValue);

    if(m_HasReachedEnd)
    {
        if(m_Tween.onEnd)
            m_Tween.onEnd();

        m_IsDecommissioned = true;
    }
}
