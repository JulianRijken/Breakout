#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <Singleton.h>

#include "Event.h"
#include "GlobalSettings.h"

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
        ~GameState() override = default;

        GameState(GameState&&) = delete;
        GameState(const GameState&) = delete;
        GameState& operator=(GameState&&) = delete;
        GameState& operator=(const GameState&) = delete;

        void ResetGame();

        [[nodiscard]] const DifficultyPreset& GetDifficultyPreset() const;
        [[nodiscard]] int GetGetScore() const;

        [[nodiscard]] bool HasBallsLeft() const;
        [[nodiscard]] int GetBallsLeft() const;
        void RemoveBall();

        bin::Event<int> m_OnScoreChanged{};
        bin::Event<int> m_OnBallsLeftChanged{};

    private:
        void OnBrickBreakMessage(const bin::Message& message);

        Difficulty m_Difficulty{ Difficulty::Easy };

        int m_BallsLeft{};
        int m_Score{};
    };
}  // namespace bout
#endif  // GAMESTATS_H
