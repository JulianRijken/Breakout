#ifndef TWEENINSTANCE_H
#define TWEENINSTANCE_H

#include "Event.h"
#include "Tween.h"

namespace bin
{
    class Node;

    class TweenInstance final : public bin::IEventListener
    {
        friend class TweenEngine;

    private:
        TweenInstance(Tween&& tween, Node& target);

        void Update();
        void Cancel();
        void OnTargetDestroyed(Node& object);

        [[nodiscard]] bool IsDecommisioned() const { return m_IsDecommissioned; }

        bool m_IsHalting{ false };
        bool m_IsDecommissioned{ false };
        bool m_HasReachedEnd{ false };
        float m_Time{ 0 };

        Node* m_Target{ nullptr };
        Tween m_Tween;
    };
}  // namespace jul
#endif // TWEENINSTANCE_H
