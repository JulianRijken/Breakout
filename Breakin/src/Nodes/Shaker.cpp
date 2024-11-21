#include "Shaker.h"

#include "GameTime.h"
#include "MathExtensions.h"

bin::Shaker::Shaker(float shakeStrength, float offsetInterval, float smoothStrength, bool doesDecay, float decayRate) :
    m_ShakeStrength(shakeStrength),
    m_OffsetInterval(offsetInterval),
    m_SmoothStrength(smoothStrength),
    m_DecayRate(decayRate),
    m_DoesDecay(doesDecay),
    m_IsShaking(not doesDecay)  // Shake by default if we don't decay
{
}

void bin::Shaker::SetDoesDecay(bool decay) { m_DoesDecay = decay; }

void bin::Shaker::SetStrength(float strength) { m_ShakeStrength = strength; }

void bin::Shaker::StartShake()
{
    m_IsShaking = true;
    m_ShakeTimer = 0.0f;
}

void bin::Shaker::StopShake() { m_IsShaking = false; }

void bin::Shaker::Update()
{
    if(m_IsShaking)
        IncrementShake();

    // We always update position as we need to return even when not shaking
    UpdatePosition();
}

void bin::Shaker::IncrementShake()
{
    // Handle shake offset
    m_OffsetTimer += GameTime::GetDeltaTime();
    if(m_OffsetTimer > m_OffsetInterval)
    {
        m_Offset = { math::RandomRange(-1.0f, 1.0f), math::RandomRange(-1.0f, 1.0f) };
        m_OffsetTimer -= m_OffsetInterval;
    }

    // We default to no decay aka 1.0f
    m_Decay = 1.0f;

    // Handle decay
    if(m_DoesDecay)
    {
        m_ShakeTimer += GameTime::GetDeltaTime();
        m_Decay = std::exp(-m_ShakeTimer / m_DecayRate);

        constexpr float epsilon = 0.001f;
        if(m_Decay < epsilon)
            m_IsShaking = false;
    }
}

void bin::Shaker::UpdatePosition()
{
    // Center when we don't shake
    const glm::vec2 targetPosition = m_IsShaking ? m_ShakeStrength * m_Offset * m_Decay : glm::vec2{ 0.0f, 0.0f };
    const glm::vec2 smoothPosition =
        math::LerpSmooth(GetLocalPosition(), targetPosition, m_SmoothStrength, GameTime::GetDeltaTime());
    SetLocalPosition(smoothPosition);
}
