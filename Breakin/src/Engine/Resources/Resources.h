#ifndef Resources_H
#define Resources_H

#include <filesystem>
#include <map>

#include "Font.h"

namespace bin
{
    class Resources final
    {
    public:
        Resources() = delete;

        static void Initialize();
        static void Cleanup();

        static const std::filesystem::path& GetAssetsPath();

        // Can be null
        [[nodiscard]] static Font* GetFont(int id);

        static void LoadFont(int id, const std::string& filePath, int size);

    private:
        static void ConfigurePath();

        inline static std::map<int, std::unique_ptr<Font>> g_FontPtrs{};
        inline static std::filesystem::path g_AssetPath{};
    };
}  // namespace jul
#endif  // Resources_H
