#ifndef GAME_H
#define GAME_H

struct SDL_Window;
struct SDL_Renderer;

namespace jul
{
    class Game final
    {
    public:
        explicit Game();
        ~Game();

        Game(Game&&) = delete;
        Game(const Game&) = delete;
        Game& operator=(Game&&) = delete;
        Game& operator=(const Game&) = delete;

    private:
        void Run();
        void RunOneFrame();

        bool m_IsApplicationQuitting{};
        SDL_Window* m_Window;

        SDL_Renderer* m_RendererPtr{};
    };
}  // namespace jul
#endif  // GAME_H
