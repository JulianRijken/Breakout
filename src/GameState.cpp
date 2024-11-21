#include "GameState.h"

#include "GlobalSettings.h"
#include "MessageQueue.h"

bout::GameState::GameState()
{
    bin::MessageQueue::AddListener(MessageType::BrickBreak, this, &GameState::OnBrickBreakMessage);
}

bool bout::GameState::HasBallsLeft() const { return m_BallsLeft > 0; }

void bout::GameState::RemoveBall()
{
    assert(HasBallsLeft() && "Trying to remove ball with no balls left");

    m_BallsLeft--;
    m_OnBallsLeftChanged.Invoke(m_BallsLeft);
}

void bout::GameState::OnBrickBreakMessage(const bin::Message& message)
{
    const auto pointsWorth = std::any_cast<int>(message.args[0]);
    m_Score += pointsWorth;
    m_OnScoreChanged.Invoke(m_Score);
}
