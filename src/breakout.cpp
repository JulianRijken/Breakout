#include "Breakout.h"

#include <GameTime.h>
#include <Input.h>
#include <MathExtensions.h>
#include <MessageQueue.h>
#include <Paddle.h>
#include <SceneGraph.h>
#include <Text.h>
#include <TweenEngine.h>

#include "Ball.h"
#include "GlobalSettings.h"
#include "HUD.h"
#include "Playfield.h"

bout::Breakout::Breakout() :
    m_CameraPtr(&bin::SceneGraph::AddNode<bin::Camera>()),
    m_PlayfieldPtr(&bin::SceneGraph::AddNode<Playfield>(glm::vec2{ 24, 22 })),
    m_PaddlePtr(&bin::SceneGraph::AddNode<Paddle>())
{
    m_PlayfieldPtr->SetParent(this);

    m_PaddlePtr->SetParent(m_PlayfieldPtr);
    m_PaddlePtr->SetLocalPosition({ 0, -m_PlayfieldPtr->GetSize().y / 2.0f });

    auto& hud = bin::SceneGraph::AddNode<HUD>(m_GameStats);
    hud.SetParent(this);

    m_CameraPtr->SetOrthoSize(m_PlayfieldPtr->GetSize().y / 2 + CAMERA_PADDING);
    m_CameraPtr->SetLocalPosition({ 0, 0 });


    SetLocalPosition({ 0.0f, m_CameraPtr->GetOrthoSize() * 2.0f });


    m_PlayfieldPtr->m_OnFieldCleared.AddListener(this, &Breakout::OnPlayfieldClearedEvent);
    bin::MessageQueue::AddListener(MessageType::BallCollided, this, &Breakout::OnWallHitMessage);
    bin::Input::Bind(InputActionName::FireBall, this, &Breakout::OnFireBallInput);

    // Move game down and spawn ball
    bin::TweenEngine::Start(
        {
            .delay = 0.5f,
            .from = GetLocalPosition().y,
            .to = 0.0f,
            .duration = 1.0f,
            .easeType = bin::EaseType::SineInOut,
            .onUpdate =
                [this](float value) {
                    SetLocalPosition({ 0, value });
                },
            .onEnd = [this]() { TySpawnBall(); },
        },
        *this);
}

bout::Breakout::~Breakout() { bin::MessageQueue::RemoveListenerInstance(this); }

void bout::Breakout::FixedUpdate()
{
    const glm::vec2 mousePositionWorld = m_CameraPtr->ScreenToWorldPosition(bin::Input::GetMousePosition());
    m_PaddlePtr->SetPaddleTargetPosition(mousePositionWorld.x);

    constexpr glm::vec2 mouseMovePlayfieldStrength{ -0.02f, -0.02f };
    constexpr float paddleMovePlayfieldStrength{ -0.04f };

    const glm::vec2 mouseOffset{ mousePositionWorld * mouseMovePlayfieldStrength };
    const glm::vec2 paddleOffset{ m_PaddlePtr->GetLocalPosition().x * paddleMovePlayfieldStrength, 0 };
    m_PlayfieldPtr->SetLocalPosition(mouseOffset + paddleOffset);
}

void bout::Breakout::Update()
{
    constexpr float decayRate = 0.1f;

    m_ShakeTimer += bin::GameTime::GetDeltaTime();
    constexpr float shakeStrength = 0.3f;

    const glm::vec2 offset = { bin::math::RandomRange(-1.0f, 1.0f), bin::math::RandomRange(-1.0f, 1.0f) };
    const float decay = std::exp(-m_ShakeTimer / decayRate);

    const glm::vec2 cameraOffset = shakeStrength * offset * decay;
    m_CameraPtr->SetLocalPosition(cameraOffset);
}

void bout::Breakout::OnWallHitMessage(const bin::Message& /*unused*/) { ShakeCamera(); }

void bout::Breakout::OnBallLostEvent()
{
    if(m_GameStats.HasBallsLeft())
        TySpawnBall();
    else
        OnGameOver();
}

void bout::Breakout::TySpawnBall()
{
    if(m_PaddlePtr->IsHoldingBall())
        return;

    auto& ball = bin::SceneGraph::AddNode<Ball>();
    m_PaddlePtr->HoldBall(ball);
    m_GameStats.RemoveBall();

    // NOTE: We use a OnBallLost instead of on destroyed
    //       this is because if we do on destroyed we get in to a
    //       destroy and create loop
    ball.m_OnBallLostEvent.AddListener(this, &Breakout::OnBallLostEvent);

    bin::MessageQueue::Broadcast(MessageType::BallSpawned);
}

void bout::Breakout::ShakeCamera() { m_ShakeTimer = 0.0f; }

void bout::Breakout::OnGameOver() { bin::SceneGraph::LoadScene(SceneName::MainMenu); }

void bout::Breakout::OnFireBallInput(const bin::InputContext& context)
{
    if(context.state != bin::ButtonState::Down)
        return;

    m_PaddlePtr->TryLaunchBall(*m_PlayfieldPtr);
}

void bout::Breakout::OnPlayfieldClearedEvent() { OnGameOver(); }
