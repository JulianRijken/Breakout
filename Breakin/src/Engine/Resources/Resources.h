#ifndef Resources_H
#define Resources_H

#include <filesystem>
#include <iostream>
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
        template<typename FontName>
        [[nodiscard]] static Font* GetFont(FontName fontName)
        {
            const int fontIndex = static_cast<int>(fontName);
            if(g_FontPtrs.contains(fontIndex))
                return g_FontPtrs.at(fontIndex).get();

            return nullptr;
        }

        template<typename FontName>
        static void LoadFont(FontName fontName, const std::string& filePath, int size)
        {
            if(size <= 0)
                throw std::runtime_error("Font size must be greater than 0");

            int fontIndex = static_cast<int>(fontName);

            if(g_FontPtrs.contains(fontIndex))
                throw std::runtime_error("Font ID already loaded: " + std::to_string(fontIndex));


            const auto fullPath = g_AssetPath / filePath;
            g_FontPtrs.emplace(fontIndex, std::make_unique<Font>(fullPath.string(), size));
        }

    private:
        static void ConfigurePath();

        inline static std::map<int, std::unique_ptr<Font>> g_FontPtrs{};
        inline static std::filesystem::path g_AssetPath{};
    };
}  // namespace jul
#endif  // Resources_H
