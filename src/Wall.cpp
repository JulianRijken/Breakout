#include "Wall.h"

#include <BoxCollider.h>
#include <MathExtensions.h>
#include <SceneGraph.h>
#include <SDL_pixels.h>
#include <Sprite.h>
#include <TweenEngine.h>

#include "GlobalSettings.h"

bout::Wall::Wall(const glm::vec2& moveDirection) :
    m_MoveDirection(moveDirection)
{
    auto& collider = bin::SceneGraph::AddNode<bin::BoxCollider>();
    collider.SetParent(this);
    collider.m_OnHit.AddListener(this, &Wall::OnHit);

    m_SpritePtr = &bin::SceneGraph::AddNode<bin::Sprite>(WALL_NORMAL_COLOR);
    m_SpritePtr->SetParent(this);
}

void bout::Wall::OnHit(const bin::Manifold&)
{
    bin::TweenEngine::Start({ .duration = WALL_HIT_MOVE_DURATION,
                              .onUpdate =
                                  [this](float value)
                              {
                                  const float curve = bin::math::EvaluateCubicBezier(BUMB_CURVE, value).y;
                                  m_SpritePtr->SetLocalPosition(m_MoveDirection * (curve / GetWorldScale().x));
                                  m_SpritePtr->SetColor(bin::math::Lerp(WALL_NORMAL_COLOR, WALL_HIT_COLOR, curve));
                              } },
                            *this);
}
