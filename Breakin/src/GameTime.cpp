#include "gametime.h"

#include <algorithm>
#include <chrono>

void bin::GameTime::Increment()
{
    static std::chrono::time_point<std::chrono::high_resolution_clock> s_LastTime{
        std::chrono::high_resolution_clock::now()
    };

    // Calculate delta time
    const auto currentTime = std::chrono::high_resolution_clock::now();
    g_DeltaTime = std::min(MAX_DELTA_TIME, std::chrono::duration<double>(currentTime - s_LastTime).count());
    s_LastTime = currentTime;

    // Update elapsed time
    g_ElapsedTime += GetDeltaTime();
}

double bin::GameTime::GetDeltaTime() { return g_DeltaTime * g_TimeScale; }

double bin::GameTime::GetUnscaledDeltaTime() { return g_DeltaTime; }

double bin::GameTime::GetFixedDeltaTime() { return g_FixedDeltaTime; }

double bin::GameTime::GetElapsedTime() { return g_ElapsedTime; }
