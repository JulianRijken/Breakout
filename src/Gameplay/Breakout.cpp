#include "Breakout.h"

#include <Audio.h>
#include <GameTime.h>
#include <Input.h>
#include <MathExtensions.h>
#include <MessageQueue.h>
#include <Paddle.h>
#include <Resources.h>
#include <SceneGraph.h>
#include <Shaker.h>
#include <Sprite.h>
#include <Text.h>
#include <TweenEngine.h>

#include "Ball.h"
#include "GameState.h"
#include "GlobalSettings.h"
#include "HUD.h"
#include "PauseMenu.h"
#include "Playfield.h"

bout::Breakout::Breakout()
{
    GameState::GetInstance().ResetGame();

    m_BackgroundFlashSpritePtr = &bin::SceneGraph::AddNode<bin::Sprite>(SDL_Color(0, 0, 0, 0));
    m_BackgroundFlashSpritePtr->SetParent(this);
    m_BackgroundFlashSpritePtr->SetLocalScale({ 1000, 1000 });

    m_PlayfieldPtr = &bin::SceneGraph::AddNode<Playfield>(glm::vec2{ 24, 22 });
    m_PlayfieldPtr->SetParent(this);

    m_CameraShakerPtr = &bin::SceneGraph::AddNode<bin::Shaker>();

    m_CameraPtr = &bin::SceneGraph::AddNode<bin::Camera>();
    m_CameraPtr->SetParent(m_CameraShakerPtr);
    m_CameraPtr->SetOrthoSize(m_PlayfieldPtr->GetSize().y / 2.0f + CAMERA_PADDING);
    m_CameraPtr->SetLocalPosition({ 0, 0 });

    m_PaddlePtr = &bin::SceneGraph::AddNode<Paddle>();
    m_PaddlePtr->SetParent(m_PlayfieldPtr);
    m_PaddlePtr->SetLocalPosition({ 0, -m_PlayfieldPtr->GetSize().y / 2.0f });

    auto& hud = bin::SceneGraph::AddNode<HUD>();
    hud.SetParent(this);

    // Bind events
    m_PlayfieldPtr->m_OnFieldCleared.AddListener(this, &Breakout::OnPlayfieldClearedEvent);
    bin::MessageQueue::AddListener(MessageType::BallCollided, this, &Breakout::OnWallHitMessage);
    bin::MessageQueue::AddListener(MessageType::BrickBreak, this, &Breakout::OnBrickBreakMessage);
    bin::Input::Bind(InputActionName::FireBall, this, &Breakout::OnFireBallInput);
    bin::Input::Bind(InputActionName::CheatSpawnBall, this, &Breakout::OnCheatSpawnBallInput);
    bin::Input::Bind(InputActionName::CheatClearField, this, &Breakout::OnCheatClearFieldInput);
    bin::Input::Bind(InputActionName::PauseGame, this, &Breakout::OnPauseGameInput);

    bin::Audio::Play(bin::Resources::GetSound(SoundName::GameStart));

    // Move game down and spawn ball
    SetLocalPosition({ 0.0f, m_CameraPtr->GetOrthoSize() * 2.0f });
    bin::TweenEngine::Start(
        {
            .delay = 0.5f,
            .from = GetLocalPosition().y,
            .to = 0.0f,
            .duration = 1.0f,
            .easeType = bin::EaseType::SineOut,
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
    MovePaddle();
    OffsetPlayfield();
}

void bout::Breakout::OnFireBallInput(const bin::InputContext& context)
{
    if(context.state != bin::ButtonState::Down)
        return;

    m_PaddlePtr->TryLaunchBall(*m_PlayfieldPtr);
}

void bout::Breakout::OnCheatSpawnBallInput(const bin::InputContext& context)
{
    if(context.state != bin::ButtonState::Down)
        return;

    auto& ball = bin::SceneGraph::AddNode<Ball>();
    ball.LaunchBall();
}

void bout::Breakout::OnCheatClearFieldInput(const bin::InputContext& context)
{
    if(context.state != bin::ButtonState::Down)
        return;

    m_PlayfieldPtr->BreakAllBricks();
}

void bout::Breakout::OnPauseGameInput(const bin::InputContext& context)
{
    if(context.state != bin::ButtonState::Down)
        return;

    if(m_GameOver)
        return;


    if(m_PauseMenuPtr == nullptr)
    {
        m_PauseMenuPtr = &bin::SceneGraph::AddNode<PauseMenu>();
        bin::GameTime::SetTimeScale(0.0f);
        bin::Audio::Play(bin::Resources::GetSound(SoundName::PauseGame));
    }
    else
    {
        bin::GameTime::SetTimeScale(1.0f);
        m_PauseMenuPtr->HideAndDestroy();
        m_PauseMenuPtr = nullptr;
        bin::Audio::Play(bin::Resources::GetSound(SoundName::UnPauseGame));
    }
}

void bout::Breakout::OnWallHitMessage(const bin::Message& /*unused*/) { m_CameraShakerPtr->StartShake(); }

void bout::Breakout::OnBrickBreakMessage(const bin::Message& /*unused*/) { FlashScreen(); }


void bout::Breakout::OnBallLostEvent()
{
    bin::Audio::Play(bin::Resources::GetSound(SoundName::BallLost));

    if(GameState::GetInstance().HasBallsLeft())
        TySpawnBall();
    else
        EndGame(false);
}

void bout::Breakout::OnPlayfieldClearedEvent() { EndGame(true); }


void bout::Breakout::TySpawnBall()
{
    if(m_PaddlePtr->IsHoldingBall())
        return;

    if(not GameState::GetInstance().HasBallsLeft())
        return;


    const float moveSpeed = GameState::GetInstance().GetDifficultyPreset().ballMoveSpeed;
    const SDL_Color ballHitColor = GameState::GetInstance().GetDifficultyPreset().ballHitColor;

    auto& ball = bin::SceneGraph::AddNode<Ball>(moveSpeed, ballHitColor);
    m_PaddlePtr->HoldBall(ball);
    GameState::GetInstance().RemoveBall();

    // NOTE: We use a OnBallLost instead of on destroyed
    //       this is because if we do on destroyed we get in to a
    //       destroy and create loop
    ball.m_OnBallLostEvent.AddListener(this, &Breakout::OnBallLostEvent);

    bin::MessageQueue::Broadcast(MessageType::BallSpawned);
}

void bout::Breakout::OffsetPlayfield()
{
    constexpr glm::vec2 mouseMovePlayfieldStrength{ -0.02f, -0.02f };
    constexpr float paddleMovePlayfieldStrength{ -0.04f };

    const glm::vec2 mousePositionWorld = m_CameraPtr->ScreenToWorldPosition(bin::Input::GetMousePosition());
    const glm::vec2 mouseOffset{ mousePositionWorld * mouseMovePlayfieldStrength };
    const glm::vec2 paddleOffset{ m_PaddlePtr->GetLocalPosition().x * paddleMovePlayfieldStrength, 0 };
    m_PlayfieldPtr->SetLocalPosition(mouseOffset + paddleOffset);
}

void bout::Breakout::MovePaddle()
{
    const glm::vec2 mousePositionWorld = m_CameraPtr->ScreenToWorldPosition(bin::Input::GetMousePosition());
    m_PaddlePtr->SetPaddleTargetPosition(mousePositionWorld.x);
}

void bout::Breakout::EndGame(bool hasWon)
{
    if(m_GameOver)
        return;

    m_GameOver = true;

    // Slow down time
    bin::TweenEngine::Start({ .from = bin::GameTime::GetTimeScale(),
                              .to = 0.0f,
                              .duration = 2.0f,
                              .ignoreTimeScale = true,
                              .easeType = bin::EaseType::SineOut,
                              .onUpdate = [](float value) { bin::GameTime::SetTimeScale(value); },
                              .onEnd =
                                  [this, hasWon]()
                              {
                                  auto ballsStillAllive = bin::SceneGraph::GetAllNodesOfClass<Ball>();
                                  for(auto&& ball : ballsStillAllive)
                                      ball->MarkForDestroy();

                                  m_PlayfieldPtr->HideWalls();

                                  // Done here as it should play right away
                                  if(hasWon)
                                      bin::Audio::Play(bin::Resources::GetSound(SoundName::GameWon));
                                  else
                                      bin::Audio::Play(bin::Resources::GetSound(SoundName::GameLost));


                                  // Move game down
                                  bin::TweenEngine::Start(
                                      {
                                          .from = 0.0f,
                                          .to = -m_CameraPtr->GetOrthoSize() * 2.0f,
                                          .duration = 1.0f,
                                          .ignoreTimeScale = true,
                                          .easeType = bin::EaseType::SineInOut,
                                          .onUpdate =
                                              [this](float value) {
                                                  SetLocalPosition({ 0, value });
                                              },
                                      },
                                      *this);

                                  // Show win or lose screen
                                  bin::TweenEngine::Start(
                                      {
                                          .delay = 1.7f,
                                          .duration = 0.0f,
                                          .ignoreTimeScale = true,
                                          .onEnd =
                                              [hasWon]()
                                          {
                                              bin::GameTime::SetTimeScale(1.0f);

                                              if(hasWon)
                                                  bin::SceneGraph::LoadScene(SceneName::GameWon);
                                              else
                                                  bin::SceneGraph::LoadScene(SceneName::GameLost);
                                          },
                                      },
                                      *this);
                              } },
                            *this);
}

void bout::Breakout::FlashScreen()
{
    bin::TweenEngine::Start(
        { .duration = BRICK_BREAK_FLASH_DURATION,
          .onUpdate =
              [this](float value)
          {
              const float curve = bin::math::EvaluateCubicBezier(BUMP_CURVE, value).y;
              const SDL_Color color = { 255, 255, 255, static_cast<Uint8>(curve * BRICK_BREAK_FLASH_ALPHA) };
              m_BackgroundFlashSpritePtr->SetColor(color);
          } },
        *this);
}
