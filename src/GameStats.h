#ifndef GAMESTATS_H
#define GAMESTATS_H

#include "Event.h"

namespace bin
{
    struct Message;
}

namespace bout
{
    class GameStats final
    {
    public:
        GameStats();
        ~GameStats();

        GameStats(GameStats&&) = delete;
        GameStats(const GameStats&) = delete;
        GameStats& operator=(GameStats&&) = delete;
        GameStats& operator=(const GameStats&) = delete;

        [[nodiscard]] bool HasBallsLeft() const;
        void RemoveBall();

        bin::Event<int> m_OnScoreChanged{};
        bin::Event<int> m_OnBallsLeftChanged{};

    private:
        void OnBrickBreakMessage(const bin::Message& message);

        int m_BallsLeft{ 5 };
        int m_Score{ 0 };
    };
}  // namespace bout
#endif  // GAMESTATS_H
