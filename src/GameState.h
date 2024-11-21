#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <Singleton.h>

#include <chrono>

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

        // NOTE: Breakout and the GameState are tightly coupled
        //       for this reason I don't use events here

        void ResetGame();
        void RemoveBall();
        void IncrementPaddleBounces();
        void IncrementBallsUsed();
        void UseCheat();

        [[nodiscard]] const DifficultyPreset& GetDifficultyPreset() const;

        [[nodiscard]] int GetBallsLeft() const;
        [[nodiscard]] int GetGetScore() const;
        [[nodiscard]] int GetBallsUsed() const;
        [[nodiscard]] int GetBricksBroken() const;
        [[nodiscard]] int GetPaddleBounces() const;
        [[nodiscard]] int GetScecondsSinceGameReset() const;

        [[nodiscard]] bool HasBallsLeft() const;
        [[nodiscard]] bool HasCheated() const;

        bin::Event<int> m_OnScoreChanged{};
        bin::Event<int> m_OnBallsLeftChanged{};

        Difficulty m_Difficulty{ Difficulty::Easy };  // NOLINT - C.131: Avoid trivial getters and setters

    private:
        void OnBrickBreakMessage(const bin::Message& message);
        void OnBallLostMessage(const bin::Message& message);
        void OnBallSpawnedMessage(const bin::Message& message);

        int m_BallsLeft{};
        int m_Score{};
        int m_BallsUsed{};
        int m_BricksBroken{};
        int m_PaddleBounces{};
        int m_BallsInScene{};
        bool m_HasCheated{};

        // This is why we hate chrono
        std::chrono::high_resolution_clock::time_point m_StartTime{ std::chrono::high_resolution_clock::now() };
    };
}  // namespace bout
#endif  // GAMESTATS_H
