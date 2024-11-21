#ifndef GAME_H
#define GAME_H

#include <string>

struct SDL_Window;
struct SDL_Renderer;

namespace bin
{
    struct InitSettings
    {
        int windowWidth = 1280;
        int windowHeight = 720;
        std::string windowTitle = "Breakin Application";
    };

    class Core final
    {
    public:
        Core();
        ~Core();

        Core(Core&&) = delete;
        Core(const Core&) = delete;
        Core& operator=(Core&&) = delete;
        Core& operator=(const Core&) = delete;

        // Requires to be public for Emscripten
        void IncrementFrame();

    private:
        // Is implemented by the game
        void PreInit(InitSettings& initSettings);
        void GameEntry();

        // We are Breakin' and Entering!
        void Run();

        float m_Lag{ 0.0f };
        bool m_IsApplicationQuitting{ false };
        SDL_Window* m_WindowPtr{ nullptr };
    };
}  // namespace bin
#endif  // GAME_H
