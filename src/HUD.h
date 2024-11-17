#ifndef HUD_H
#define HUD_H

#include <Event.h>
#include <Node.h>

namespace bin
{
    class Text;
}

namespace bout
{
    class GameStats;

    class HUD final : public bin::Node, public bin::IEventListener
    {
    public:
        HUD(GameStats& gameStats);

    private:
        void OnScoreChanged(int score);

        bin::Text* m_ScoreText{};
    };
}  // namespace bout

#endif  // HUD_H
