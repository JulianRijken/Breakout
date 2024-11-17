#include "Breakout.h"

#include <fmt/core.h>
#include <Font.h>
#include <GameTime.h>
#include <Input.h>
#include <Locator.h>
#include <MathExtensions.h>
#include <MessageQueue.h>
#include <Paddle.h>
#include <Renderer.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <SDL_mouse.h>
#include <Text.h>
#include <Texture.h>

#include "Ball.h"
#include "HUD.h"
#include "Playfield.h"

bout::Breakout::Breakout() :
    m_CameraPtr(&bin::SceneGraph::AddNode<bin::Camera>()),
    m_PlayfieldPtr(&bin::SceneGraph::AddNode<Playfield>(glm::vec2{ 24, 22 })),
    m_PaddlePtr(&bin::SceneGraph::AddNode<Paddle>())
{
    m_PaddlePtr->SetParent(m_PlayfieldPtr);
    m_PaddlePtr->SetLocalPosition({ 0, -m_PlayfieldPtr->GetSize().y / 2.0f });

    auto& hud = bin::SceneGraph::AddNode<HUD>(m_GameStats);
    hud.SetParent(this);

    m_CameraPtr->SetOrthoSize(m_PlayfieldPtr->GetSize().y / 2 + CAMERA_PADDING);
    m_CameraPtr->SetLocalPosition({ 0, 0 });

    bin::MessageQueue::AddListener(MessageType::OnWallHit, this, &Breakout::OnWallHitMessage);
    bin::Input::Bind(InputActionName::FireBall, this, &Breakout::OnFireBallInput);
}

void bout::Breakout::FixedUpdate()
{
    glm::ivec2 mousePosition{};
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    const glm::vec2 mousePositionWorld = m_CameraPtr->ScreenToWorldPosition(mousePosition);
    m_PaddlePtr->SetPaddleTargetPosition(mousePositionWorld.x);

    constexpr glm::vec2 mouseMovePlayfieldStrenght{ -0.05f, -0.02f };
    m_PlayfieldPtr->SetLocalPosition(mousePositionWorld * mouseMovePlayfieldStrenght);
}

void bout::Breakout::Update()
{
    const float decayRate = 0.1f;

    m_ShakeTimer += bin::GameTime::GetDeltaTime();
    const float shakeStrength = 0.3f;

    const glm::vec2 offset = { bin::math::RandomRange(-1.0f, 1.0f), bin::math::RandomRange(-1.0f, 1.0f) };
    const float decay = std::exp(-m_ShakeTimer / decayRate);

    const glm::vec2 cameraOffset = shakeStrength * offset * decay;
    m_CameraPtr->SetLocalPosition(cameraOffset);
}

void bout::Breakout::OnWallHitMessage(const bin::Message& /*unused*/) { ShakeCamera(); }

void bout::Breakout::ShakeCamera() { m_ShakeTimer = 0.0f; }

void bout::Breakout::OnFireBallInput(const bin::InputContext& context)
{
    if(context.state != bin::ButtonState::Down)
        return;

    if(m_PaddlePtr->IsHoldingBall())
        m_PaddlePtr->FireBall();
    else
        m_PaddlePtr->GetBallReady();
}
