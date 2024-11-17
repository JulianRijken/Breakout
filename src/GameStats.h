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

        void OnBrickBreakMessage(const bin::Message& message);

        bin::Event<int> m_OnScoreChanged{};

    private:
        int m_BricksBroken{};
        int m_Score{};
    };
}  // namespace bout
#endif  // GAMESTATS_H
