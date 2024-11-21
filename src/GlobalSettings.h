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
        std::string name{};
        int startingBallCount{};
        float ballMoveSpeed{};
        SDL_Color ballHitColor{};
    };

    const std::unordered_map<Difficulty, DifficultyPreset> DIFFICULTY_SETTINGS{
        {Difficulty::Noob,
         {
         .name = "NOOB",
         .startingBallCount = 12,
         .ballMoveSpeed = 10.0f,
         .ballHitColor = { 65, 224, 70, 255 },
         }                                                                                                        },

        {Difficulty::Easy,
         { .name = "EASY", .startingBallCount = 5, .ballMoveSpeed = 18.0f, .ballHitColor = { 45, 172, 214, 255 } }},

        {Difficulty::Hard,
         { .name = "HARD", .startingBallCount = 3, .ballMoveSpeed = 24.0f, .ballHitColor = { 235, 59, 59, 255 } } },

        {Difficulty::Nerd,
         { .name = "NERD", .startingBallCount = 1, .ballMoveSpeed = 28.0f, .ballHitColor = { 0, 0, 0, 255 } }     }
    };


    enum class MessageType
    {
        BallCollided,

        // arg[0] = int pointsWorth
        BrickBreak,

        BallSpawned,
        BallLost,
        FieldClearOfBalls,
        BallLaunched,
        BallSetToLaunch
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
