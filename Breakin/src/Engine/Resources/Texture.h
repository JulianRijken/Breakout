#ifndef TEXTURE_H
#define TEXTURE_H
#include <glm/vec2.hpp>

struct SDL_Texture;

namespace bin
{
    // Simple RAII wrapper for SDL_Texture
    class Texture final
    {
    public:
        explicit Texture(SDL_Texture* texture);
        ~Texture();

        Texture(Texture&&) = delete;
        Texture(const Texture&) = delete;
        Texture& operator=(Texture&&) = delete;
        Texture& operator=(const Texture&) = delete;

        [[nodiscard]] SDL_Texture* GetSDLTexture() const;
        [[nodiscard]] glm::ivec2 GetSize() const;

	private:
		SDL_Texture* m_Texture;
    };
}
#endif  // TEXTURE_H
