#include "Paddle.h"

#include <GameTime.h>
#include <MathExtensions.h>
#include <MessageQueue.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include <algorithm>

#include "Ball.h"
#include "BoxCollider.h"
#include "GlobalSettings.h"


bout::Paddle::Paddle()
{
    auto& boxColliderPtr = bin::SceneGraph::AddNode<bin::BoxCollider>(glm::vec2{ 2, 0.5f }, bout::collisionLayer::PADDLE);
    boxColliderPtr.SetParent(this);
}

void bout::Paddle::SetPaddleTargetPosition(float targetPosition)
{
    m_PaddleTargetPosition = std::clamp(targetPosition, -MAX_MOVE_DISTANCE, MAX_MOVE_DISTANCE);
}

void bout::Paddle::HoldBall(bout::Ball& ball)
{
    assert(m_HoldingBallPtr == nullptr && "Trying to get a ball ready when there is still one");

    m_HoldingBallPtr = &ball;
    m_HoldingBallPtr->SetParent(this);
    m_HoldingBallPtr->SetLocalPosition({ 0, 1 });
}

void bout::Paddle::TryLaunchBall(Node& parent)
{
    if(not IsHoldingBall())
        return;

    m_HoldingBallPtr->SetParent(&parent);
    m_HoldingBallPtr->LaunchBall();
    m_HoldingBallPtr = nullptr;

    bin::MessageQueue::Broadcast(MessageType::BallLaunched);
}

bool bout::Paddle::IsHoldingBall() const { return m_HoldingBallPtr != nullptr; }

void bout::Paddle::FixedUpdate()
{
    m_PaddlePosition =
        bin::math::LerpSmooth(m_PaddlePosition, m_PaddleTargetPosition, MOVE_DURATION, bin::GameTime::GetDeltaTime());

    SetLocalPosition({ m_PaddlePosition, GetLocalPosition().y });
}

void bout::Paddle::Draw(const bin::Renderer& renderer)
{
    renderer.DrawBox({ GetWorldPosition() }, { 2, 0.5 }, { 0.5f, 0.5f });
}
