#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <Singleton.h>

#include "Event.h"

namespace bin
{
    struct Message;
}

namespace bout
{
    class GameState final : public bin::Singleton<GameState>
    {
    public:
        GameState();
        ~GameState() = default;

        GameState(GameState&&) = delete;
        GameState(const GameState&) = delete;
        GameState& operator=(GameState&&) = delete;
        GameState& operator=(const GameState&) = delete;

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
