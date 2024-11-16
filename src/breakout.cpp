#include "Breakout.h"

#include <fmt/core.h>
#include <GameTime.h>
#include <Locator.h>
#include <MathExtensions.h>
#include <Paddle.h>
#include <Renderer.h>
#include <SceneGraph.h>
#include <SDL_mouse.h>

#include "Ball.h"

bout::Breakout::Breakout()
{
    m_Camera = bin::SceneGraph::AddNode<bin::Camera>();
    m_Camera->SetOrthoSize(10);
    m_Camera->SetLocalPosition({ 0, 5 });

    bin::SceneGraph::AddNode<Paddle>();

    m_Ball = bin::SceneGraph::AddNode<Ball>();
}

void bout::Breakout::Update()
{
    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);


    const float time = bin::GameTime::GetElapsedTime();
    m_Camera->SetLocalPosition({ time, time });


    const glm::vec2 mousePosition = { mouseX, mouseY };
    const glm::vec2 mousePositionWorld = m_Camera->ScreenToWorldPosition(mousePosition);


    m_paddleTargetPostion = std::clamp(mousePositionWorld.x, -10.0f, 10.0f);
    m_paddleTargetPostion = std::round(m_paddleTargetPostion);

    m_PaddlePosition = bin::math::LerpSmooth(
        m_PaddlePosition, m_paddleTargetPostion, PADDLE_MOVE_DURATION, bin::GameTime::GetDeltaTime());
}

void bout::Breakout::Draw() const
{
    auto& renderer = bin::Locator::Get<bin::Renderer>();

    const float time = bin::GameTime::GetElapsedTime();
    constexpr float distance = 5;
    glm::vec2 pos = { std::cos(time), std::sin(time) };
    pos *= distance;

    renderer.DrawLine({ 0, 0 }, pos);

    renderer.DrawLine({ -5, 0 }, { 5, 0 }, { 217, 64, 237, 255 });
    renderer.DrawLine({ 0, -5 }, { 0, 5 }, { 217, 64, 237, 255 });
    renderer.DrawWireBox({ 0, 0 }, { 5, 5 });
    renderer.DrawWireBox({ 5, 5 }, { 5, 5 });


    renderer.DrawBox({ m_PaddlePosition, 0 }, { 1, 1 }, { 0.5f, 0.5f });
}
