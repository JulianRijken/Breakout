#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <cstdint>

namespace bout
{
    enum class MessageType
    {
        OnWallHit,
        OnPaddleHit,

        // arg[0] = int pointsWorth
        OnBrickBreak,

        // arg[0] = int score
        OnScoreChange
    };

    enum class InputActionName
    {
        ForceRestart,
        FireBall
    };

    enum class SceneName
    {
        Game,
        MainMenu
    };

    enum class FontName
    {
        NES_Font
    };

    namespace collisionLayer
    {
        constexpr uint16_t Index(int index) { return 1 << index; }

        constexpr uint16_t ALL = 0xFFFF;
        constexpr uint16_t BRICK = Index(1);
        constexpr uint16_t PADDLE = Index(2);
    }  // namespace collisionLayer
}  // namespace bout


#endif  // GLOBALSETTINGS_H
