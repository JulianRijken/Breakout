#include "GameTime.h"

#include <algorithm>
#include <chrono>

void bin::GameTime::IncrementFrame()
{
    static std::chrono::time_point<std::chrono::high_resolution_clock> s_LastTime{
        std::chrono::high_resolution_clock::now()
    };

    // Calculate delta time
    const auto currentTime = std::chrono::high_resolution_clock::now();
    g_DeltaTime = std::min(MAX_DELTA_TIME, std::chrono::duration<float>(currentTime - s_LastTime).count());
    s_LastTime = currentTime;

    // Update elapsed time
    g_ElapsedTime += GetDeltaTime();
}

float bin::GameTime::GetDeltaTime() { return g_DeltaTime * g_TimeScale; }

float bin::GameTime::GetUnscaledDeltaTime() { return g_DeltaTime; }

float bin::GameTime::GetFixedDeltaTime() { return g_FixedDeltaTime; }

float bin::GameTime::GetElapsedTime() { return g_ElapsedTime; }

float bin::GameTime::GetTimeScale() { return g_TimeScale; }

void bin::GameTime::SetTimeScale(float timeScale) { g_TimeScale = std::max(0.0f, timeScale); }
