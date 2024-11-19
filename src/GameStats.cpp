#include "GameStats.h"

#include "GlobalSettings.h"
#include "MessageQueue.h"

bout::GameStats::GameStats()
{
    bin::MessageQueue::AddListener(MessageType::BrickBreak, this, &GameStats::OnBrickBreakMessage);
}

bool bout::GameStats::HasBallsLeft() const { return m_BallsLeft > 0; }

void bout::GameStats::RemoveBall()
{
    assert(HasBallsLeft() && "Trying to remove ball with no balls left");

    m_BallsLeft--;
    m_OnBallsLeftChanged.Invoke(m_BallsLeft);
}

void bout::GameStats::OnBrickBreakMessage(const bin::Message& message)
{
    const auto pointsWorth = std::any_cast<int>(message.args[0]);
    m_Score += pointsWorth;
    m_OnScoreChanged.Invoke(m_Score);
}

bout::GameStats::~GameStats() { bin::MessageQueue::RemoveListenerInstance(this); }
