#ifndef GAMETIME_H
#define GAMETIME_H

namespace bin
{
    class GameTime final
    {
        friend class Core;

    public:
        [[nodiscard]] static float GetDeltaTime();
        [[nodiscard]] static float GetUnscaledDeltaTime();
        [[nodiscard]] static float GetFixedDeltaTime();
        [[nodiscard]] static float GetElapsedTime();

    private:
        static void IncrementFrame();

        inline static constexpr float MAX_DELTA_TIME{ 1.0f / 30.0f };
        inline static float g_FixedDeltaTime{ 1.0f / 120.0f };

        inline static float g_ElapsedTime{ 0.0f };
        inline static float g_DeltaTime{ 0.0f };
        inline static float g_TimeScale{ 1.0f };
    };
}  // namespace bin

#endif  // GAMETIME_H
