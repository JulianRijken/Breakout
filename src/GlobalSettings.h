#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <MathExtensions.h>

#include <cstdint>


namespace bout
{
    enum class MessageType
    {
        BallCollided,

        // arg[0] = int pointsWorth
        BrickBreak,

        BallSpawned,
        BallLaunched
    };

    enum class InputActionName
    {
        ForceRestart,
        FireBall
    };

    enum class SceneName
    {
        Testing,
        Game,
        MainMenu,
        ScoreScreen
    };

    enum class FontName
    {
        NES_Font
    };

    enum class SoundName
    {
        WallHit
    };

    namespace collisionLayer
    {
        constexpr uint16_t Index(int index) { return 1 << index; }

        constexpr uint16_t ALL = 0xFFFF;
        constexpr uint16_t BRICK = Index(1);
        constexpr uint16_t PADDLE = Index(2);
    }  // namespace collisionLayer

    constexpr bin::math::CubicCurve BUMP_CURVE{
        {   0,    0},
        {0.28, 2.21},
        { 0.2,    0},
        {   1,    0}
    };
}  // namespace bout


#endif  // GLOBALSETTINGS_H
