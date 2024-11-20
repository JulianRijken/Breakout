#include "Brick.h"

#include <BoxCollider.h>
#include <MessageQueue.h>
#include <Renderer.h>
#include <SceneGraph.h>

#include "GlobalSettings.h"


bout::Brick::Brick(int pointsWorth, const glm::vec2& brickSize, const SDL_Color& brickColor) :
    m_PointsWorth(pointsWorth),
    m_BrickSize(brickSize),
    m_BrickColor(brickColor)
{
    auto& boxCollider = bin::SceneGraph::AddNode<bin::BoxCollider>(m_BrickSize, bout::collisionLayer::BRICK);
    boxCollider.SetParent(this);
    boxCollider.m_OnHit.AddListener(this, &Brick::OnHit);
}

void bout::Brick::Break()
{
    if(m_Broken)
        return;

    m_Broken = true;
    bin::MessageQueue::Broadcast(MessageType::BrickBreak, { m_PointsWorth });

    // TODO: Allow bricks to spawn balls when the destroy
    //       Needs tweening because it needs to hold the ball for a sec
    //       and only after that release it slowly
    //       so the ball also needs a different function that shoot
    // if(bin::math::RandomValue() > 0.9f)
    // {
    //     auto& ball = bin::SceneGraph::AddNode<Ball>();
    //     ball.SetWorldPosition(GetWorldPosition());
    //     ball.ShootBall();
    // }

    // TODO: Use m_Broken to keep brick alive while destroying collider
    MarkForDestroy();
}

void bout::Brick::Draw(const bin::Renderer& renderer)
{
    renderer.DrawRect(GetWorldPosition(), m_BrickSize, { 0.5f, 0.5f }, m_BrickColor);
}

void bout::Brick::OnHit(const bin::Manifold&) { Break(); }
