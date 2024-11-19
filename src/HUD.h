#ifndef HUD_H
#define HUD_H

#include <Event.h>
#include <Node.h>

namespace bin
{

    class Message;
    class Text;
}

namespace bout
{
    class GameStats;

    class HUD final : public bin::Node, public bin::IEventListener
    {
    public:
        HUD(GameStats& gameStats);
        ~HUD() override;

        HUD(HUD&&) = delete;
        HUD(const HUD&) = delete;
        HUD& operator=(HUD&&) = delete;
        HUD& operator=(const HUD&) = delete;


    private:
        void OnScoreChanged(int score);
        void OnBallsLeftChanged(int ballsLeft);

        void OnBallLaunchedMessage(const bin::Message& message);
        void OnBallSpawnedMessage(const bin::Message& message);


        bin::Text* m_ScoreText{};
        bin::Text* m_BallsLeftText{};
        bin::Text* m_LaunchBallText{};
    };
}  // namespace bout

#endif  // HUD_H
