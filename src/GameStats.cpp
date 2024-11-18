#include "GameStats.h"

#include "GlobalSettings.h"
#include "MessageQueue.h"

bout::GameStats::GameStats()
{
    bin::MessageQueue::AddListener(MessageType::OnBrickBreak, this, &GameStats::OnBrickBreakMessage);
}

void bout::GameStats::OnBrickBreakMessage(const bin::Message& message)
{
    auto pointsWorth = std::any_cast<int>(message.args[0]);
    m_Score += pointsWorth;
    m_OnScoreChanged.Invoke(m_Score);
}

bout::GameStats::~GameStats() { bin::MessageQueue::RemoveListenerInstance(this); }
