#ifndef GAME_H
#define GAME_H

#include <string>

#include <glm/vec2.hpp>

struct SDL_Window;
struct SDL_Renderer;

namespace bin
{
    struct InitSettings
    {
        glm::ivec2 windowSize = { 1280, 720 };
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

        // TODO: Not ideal to have this static
        //       this is for g_IsApplicationQuitting
        //       in the future consider a different way for the game to communicate it wants to quit
        static void QuitGame();

    private:
        // Is implemented by the game
        [[nodiscard]] InitSettings Configure() const;

        // Is implemented by the game
        void GameEntry();

        void Run();

        // We hate this being static!
        // But the game needs it to communicate it wants to quit :(
        // TODO: Solve this in the future... :)
        inline static bool g_IsApplicationQuitting{ false };

        float m_Lag{ 0.0f };
        SDL_Window* m_WindowPtr{ nullptr };
    };
}  // namespace bin
#endif  // GAME_H
