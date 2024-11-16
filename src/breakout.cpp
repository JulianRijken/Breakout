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
#include "Playfield.h"

bout::Breakout::Breakout() :
    m_Camera(bin::SceneGraph::AddNode<bin::Camera>()),
    m_PlayfieldPtr(bin::SceneGraph::AddNode<Playfield>(glm::vec2{ 24, 22 })),
    m_PaddlePtr(bin::SceneGraph::AddNode<Paddle>())
{
    m_PaddlePtr->SetParent(m_PlayfieldPtr);
    m_PaddlePtr->SetLocalPosition({ 0, -m_PlayfieldPtr->GetSize().y / 2.0f });


    auto* ball = bin::SceneGraph::AddNode<Ball>();
    ball->SetParent(m_PaddlePtr);
    ball->SetLocalPosition({ 0, 1 });


    m_Camera->SetOrthoSize(m_PlayfieldPtr->GetSize().y / 2 + CAMERA_PADDING);
    m_Camera->SetLocalPosition({ 0, 0 });
}

void bout::Breakout::Update()
{
    int mouseX{};
    int mouseY{};
    SDL_GetMouseState(&mouseX, &mouseY);

    const glm::vec2 mousePosition = { mouseX, mouseY };
    const glm::vec2 mousePositionWorld = m_Camera->ScreenToWorldPosition(mousePosition);

    m_PaddlePtr->SetPaddleTargetPosition(mousePositionWorld.x);

    // Testing
    // const float time = bin::GameTime::GetElapsedTime();
    // m_Camera->SetLocalPosition({ time, time });
    // m_PlayfieldPtr->SetLocalPosition({ time, time });
}

void bout::Breakout::Draw()
{
    // const float time = bin::GameTime::GetElapsedTime();
    // constexpr float distance = 5;
    // glm::vec2 pos = { std::cos(time), std::sin(time) };
    // pos *= distance;

    // renderer.DrawLine({ 0, 0 }, pos);

    // renderer.DrawLine({ -5, 0 }, { 5, 0 }, { 217, 64, 237, 255 });
    // renderer.DrawLine({ 0, -5 }, { 0, 5 }, { 217, 64, 237, 255 });

    // renderer.DrawWireBox({ 0, 0 }, { 5, 5 });
    // renderer.DrawWireBox({ 5, 5 }, { 5, 5 });
}
