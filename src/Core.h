#ifndef GAME_H
#define GAME_H

#include <Breakout.h>

#include <memory>

struct SDL_Window;
struct SDL_Renderer;

namespace jul
{
    class Core final
    {
    public:
        explicit Core();
        ~Core();

        Core(Core&&) = delete;
        Core(const Core&) = delete;
        Core& operator=(Core&&) = delete;
        Core& operator=(const Core&) = delete;

        // Requres to be public for Emscripten
        void RunOneFrame();

    private:
        void Run();

        double m_Lag{ 0.0 };
        bool m_IsApplicationQuitting{ false };
        SDL_Window* m_WindowPtr{ nullptr };
        std::unique_ptr<Breakout> m_BreakoutPtr{};
    };
}  // namespace jul
#endif  // GAME_H
