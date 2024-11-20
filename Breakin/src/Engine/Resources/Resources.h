#ifndef Resources_H
#define Resources_H

#include <filesystem>
#include <map>

#include "Font.h"
#include "Sound.h"


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

        // Can be null
        template<typename SoundName>
        [[nodiscard]] static Sound* GetSound(SoundName fontName)
        {
            const int soundIndex = static_cast<int>(fontName);
            if(g_SoundPtrs.contains(soundIndex))
                return g_SoundPtrs.at(soundIndex).get();

            return nullptr;
        }

        template<typename FontName>
        static void LoadFont(FontName fontName, const std::filesystem::path& filePath, int size)
        {
            if(size <= 0)
                throw std::runtime_error("Font size must be greater than 0");

            int fontIndex = static_cast<int>(fontName);

            if(g_FontPtrs.contains(fontIndex))
                throw std::runtime_error("Font ID already loaded: " + std::to_string(fontIndex));


            const auto fullPath = g_AssetPath / filePath;
            g_FontPtrs.emplace(fontIndex, std::make_unique<Font>(fullPath.string(), size));
        }

        template<typename SoundName>
        static void LoadSound(SoundName soundName, const std::filesystem::path& filePath)
        {
            int soundIndex = static_cast<int>(soundName);

            if(g_SoundPtrs.contains(soundIndex))
                throw std::runtime_error("Sound ID already loaded: " + std::to_string(soundIndex));

            const auto fullPath = g_AssetPath / filePath;
            g_SoundPtrs.emplace(soundIndex, std::make_unique<Sound>(fullPath.string()));
        }

    private:
        static void ConfigurePath();

        inline static std::map<int, std::unique_ptr<Font>> g_FontPtrs{};
        inline static std::map<int, std::unique_ptr<Sound>> g_SoundPtrs{};
        inline static std::filesystem::path g_AssetPath{};
    };
}  // namespace jul
#endif  // Resources_H
