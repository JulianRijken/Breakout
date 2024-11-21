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
        CheatOpenMainMenu,
        CheatOpenGame,
        CheatOpenWinScreen,
        CheatOpenLoseScreen,
        CheatOpenScoreScreen,
        CheatSpawnBall,
        CheatClearField,
        PauseGame,
        FireBall
    };

    enum class SceneName
    {
        Game,
        MainMenu,
        GameLost,
        GameWon,
        Score,
    };

    enum class FontName
    {
        NES_Font
    };

    enum class SoundName
    {
        WallHit,
        PaddleHit,
        BrickBreak,
        ButtonPress,
        ButtonRelease,
        ButtonHover,
        GameStart,
        GameLost,
        GameWon,
        GameStartup,
        PauseGame,
        UnPauseGame,
        BallLost
    };

    namespace collisionLayer
    {
        constexpr uint16_t Index(int index) { return 1 << index; }
        constexpr uint16_t ALL = 0xFFFF;
        constexpr uint16_t BRICK = Index(1);
        constexpr uint16_t PADDLE = Index(2);
    }  // namespace collisionLayer

    constexpr bin::math::CubicCurve BUMP_CURVE{
        { 0.0f,  0.0f},
        {0.28f, 2.21f},
        { 0.2f,  0.0f},
        { 1.0f,  0.0f}
    };
}  // namespace bout


#endif  // GLOBALSETTINGS_H
