#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>

#include <filesystem>

namespace bin
{
    // Simple RAII wrapper for TTF_Font
    class Font final
    {
    public:
        Font(const std::filesystem::path& fullPath, int size);
        ~Font();

		Font(Font&&) = delete;
		Font(const Font &) = delete;
		Font& operator= (Font&&) = delete;
		Font& operator= (const Font&) = delete;

        [[nodiscard]] int GetSize() const;
        [[nodiscard]] TTF_Font* GetFont() const;

    private:
        int m_Size;
        TTF_Font* m_Font;
    };
}  // namespace bin
#endif // FONT_H
