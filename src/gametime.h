#ifndef GAMETIME_H
#define GAMETIME_H

namespace jul
{
    class GameTime final
    {
    public:
        static void Increment();

        [[nodiscard]] static double GetDeltaTime();
        [[nodiscard]] static double GetUnscaledDeltaTime();
        [[nodiscard]] static double GetFixedDeltaTime();
        [[nodiscard]] static double GetElapsedTime();

    private:
        inline static constexpr double MAX_DELTA_TIME{ 1.0 / 30.0 };
        inline static double g_FixedDeltaTime{ 1.0 / 120.0 };

        inline static double g_ElapsedTime{ 0.0 };
        inline static double g_DeltaTime{ 0.0 };
        inline static double g_TimeScale{ 1.0 };
    };
}  // namespace jul

#endif  // GAMETIME_H
