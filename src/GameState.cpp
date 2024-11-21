#include "GameState.h"

#include "GlobalSettings.h"
#include "MessageQueue.h"

bout::GameState::GameState()
{
    bin::MessageQueue::AddListener(MessageType::BrickBreak, this, &GameState::OnBrickBreakMessage);
    bin::MessageQueue::AddListener(MessageType::BallSpawned, this, &GameState::OnBallSpawnedMessage);
    bin::MessageQueue::AddListener(MessageType::BallLost, this, &GameState::OnBallLostMessage);
}

void bout::GameState::ResetGame()
{
    m_BallsLeft = GetDifficultyPreset().startingBallCount;
    m_Score = 0;
    m_HasCheated = false;
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_PaddleBounces = 0;
    m_BricksBroken = 0;
    m_BallsLost = 0;
    m_BallsInScene = 0;
}

const bout::DifficultyPreset& bout::GameState::GetDifficultyPreset() const
{
    return DIFFICULTY_SETTINGS.at(m_Difficulty);
}

int bout::GameState::GetBallsLeft() const { return m_BallsLeft; }

int bout::GameState::GetGetScore() const { return m_Score; }

int bout::GameState::GetBallsLost() const { return m_BallsLost; }

int bout::GameState::GetBricksBroken() const { return m_BricksBroken; }

int bout::GameState::GetPaddleBounces() const { return m_PaddleBounces; }

int bout::GameState::GetScecondsSinceGameReset() const
{
    auto endTime = std::chrono::high_resolution_clock::now();
    return static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(endTime - m_StartTime).count());
}

bool bout::GameState::HasBallsLeft() const { return GetBallsLeft() > 0; }

bool bout::GameState::HasCheated() const { return m_HasCheated; }


void bout::GameState::RemoveBall()
{
    assert(HasBallsLeft() && "Trying to remove ball with no balls left");

    m_BallsLeft--;
    m_OnBallsLeftChanged.Invoke(m_BallsLeft);
}

void bout::GameState::IncrementPaddleBounces() { m_PaddleBounces++; }

void bout::GameState::IncrementBallsLost() { m_BallsLost++; }

void bout::GameState::UseCheat() { m_HasCheated = true; }

void bout::GameState::OnBrickBreakMessage(const bin::Message& message)
{
    const auto pointsWorth = std::any_cast<int>(message.args[0]);
    m_BricksBroken++;
    m_Score += pointsWorth;
    m_OnScoreChanged.Invoke(m_Score);
}

void bout::GameState::OnBallLostMessage(const bin::Message&)
{
    m_BallsInScene--;
    assert(m_BallsInScene >= 0 && "Ball lost without getting spawned");

    if(m_BallsInScene == 0)
        bin::MessageQueue::Broadcast(MessageType::FieldClearOfBalls);
}

void bout::GameState::OnBallSpawnedMessage(const bin::Message&) { m_BallsInScene++; }
