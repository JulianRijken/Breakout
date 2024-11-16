#include "Paddle.h"

#include <GameTime.h>
#include <MathExtensions.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include <algorithm>

#include "BoxCollider.h"

bout::Paddle::Paddle()
{
    auto* boxColliderPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 2, 0.5f });
    boxColliderPtr->SetParent(this);
}

void bout::Paddle::SetPaddleTargetPosition(float targetPosition)
{
    m_PaddleTargetPostion = std::clamp(targetPosition, -MAX_MOVE_DISTANCE, MAX_MOVE_DISTANCE);
}

void bout::Paddle::FixedUpdate()
{
    m_PaddlePosition =
        bin::math::LerpSmooth(m_PaddlePosition, m_PaddleTargetPostion, MOVE_DURATION, bin::GameTime::GetDeltaTime());

    SetLocalPosition({ m_PaddlePosition, GetLocalPosition().y });
}

void bout::Paddle::Draw()
{
    auto& renderer = bin::Locator::Get<bin::Renderer>();
    renderer.DrawBox({ GetWorldPosition() }, { 2, 0.5 }, { 0.5f, 0.5f });
}
