#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <MathExtensions.h>
#include <SDL_pixels.h>

#include <cstdint>
#include <unordered_map>

namespace bout
{
    enum class Difficulty
    {
        Noob,
        Easy,
        Hard,
        Nerd
    };

    struct DifficultyPreset
    {
        int startingBallCount{};
        float ballMoveSpeed{};
        SDL_Color ballHitColor{};
    };

    const std::unordered_map<Difficulty, DifficultyPreset> DIFFICULTY_SETTINGS{
        {Difficulty::Noob, { .startingBallCount = 10, .ballMoveSpeed = 10.0f, .ballHitColor = { 50, 255, 0, 255 } }},

        {Difficulty::Easy,  { .startingBallCount = 5, .ballMoveSpeed = 16.0f, .ballHitColor = { 0, 50, 255, 255 } }},

        {Difficulty::Hard,  { .startingBallCount = 3, .ballMoveSpeed = 22.0f, .ballHitColor = { 255, 50, 0, 255 } }},

        {Difficulty::Nerd,     { .startingBallCount = 1, .ballMoveSpeed = 30.0f, .ballHitColor = { 0, 0, 0, 255 } }}
    };


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
