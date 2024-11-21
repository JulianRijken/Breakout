#ifndef SHAKER_H
#define SHAKER_H

#include "Node.h"

namespace bin
{
    class Shaker final : public Node
    {
    public:
        Shaker(float shakeStrength = 0.4f, float offsetInterval = 0.03f, float smoothStrength = 0.05f,
               bool doesDecay = true, float decayRate = 0.12f);

        ~Shaker() override = default;
        Shaker(Shaker&&) = delete;
        Shaker(const Shaker&) = delete;
        Shaker& operator=(Shaker&&) = delete;
        Shaker& operator=(const Shaker&) = delete;

        void SetDoesDecay(bool decay);
        void SetStrength(float strength);

        void StartShake();
        void StopShake();

    private:
        void Update() override;

        void IncrementShake();
        void UpdatePosition();

        float m_ShakeStrength;
        float m_OffsetInterval;
        float m_SmoothStrength;
        float m_DecayRate;

        bool m_DoesDecay;
        bool m_IsShaking;

        glm::vec2 m_Offset{};

        float m_Decay{};
        float m_ShakeTimer{};
        float m_OffsetTimer{};
    };

}  // namespace bin

#endif  // SHAKER_H
