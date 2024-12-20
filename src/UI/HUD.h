#ifndef HUD_H
#define HUD_H

#include <Event.h>
#include <Node.h>
#include <SDL_pixels.h>


namespace bin
{

    class Shaker;
    struct Message;
    class Text;
}

namespace bout
{
    class GameState;

    class HUD final : public bin::Node, public bin::IEventListener
    {
    public:
        HUD();
        ~HUD() override;

        HUD(HUD&&) = delete;
        HUD(const HUD&) = delete;
        HUD& operator=(HUD&&) = delete;
        HUD& operator=(const HUD&) = delete;

    private:
        void OnScoreChangedEvent(int score);
        void OnBallsLeftChangedEvent(int ballsLeft);

        void OnBallLaunchedMessage(const bin::Message& message);
        void OnBallSetToLaunch(const bin::Message& message);

        void UpdateBallsLeftText(int ballsLeft);
        void UpdateScoreText(int score);

        static constexpr SDL_Color FULL_BALLS_COLOR{ 200, 200, 200, 255 };
        static constexpr SDL_Color NO_BALLS_COLOR{ 255, 50, 50, 255 };
        static constexpr float LAUNCH_BALL_TEXT_SIZE{ 0.8f };
        static constexpr float LAUNCH_BALL_TEXT_SHOW_DURATION{ 0.5f };
        static constexpr float FULL_BALLS_SHAKE_STRENGTH{ 0.0f };
        static constexpr float NO_BALLS_SHAKE_STRENGTH{ 0.15f };


        bin::Shaker* m_BallsLeftShaker{};
        bin::Text* m_ScoreText{};
        bin::Text* m_BallsLeftText{};
        bin::Text* m_LaunchBallText{};
    };
}  // namespace bout

#endif  // HUD_H
