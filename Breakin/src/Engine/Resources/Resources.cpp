#include "Resources.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

void bin::Resources::Initialize()
{
    ConfigurePath();

    if (TTF_Init() != 0)
        throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
}

void bin::Resources::Cleanup()
{
    g_FontPtrs.clear();
    TTF_Quit();
}

const std::filesystem::path& bin::Resources::GetAssetsPath() { return g_AssetPath; }


void bin::Resources::ConfigurePath()
{
#if __EMSCRIPTEN__
    g_AssetPath = "/Assets/";
#else
    g_AssetPath = "./Assets/";

    // Check if the Content folder is in the parent directory
    if(not std::filesystem::exists(g_AssetPath))
        g_AssetPath = "../Assets/";
#endif

    if(not std::filesystem::exists(g_AssetPath))
    {
        std::cerr << "Content folder not found in directory: " << g_AssetPath << "\n"
                  << "Absolute Path: " << absolute(g_AssetPath) << '\n'
                  << "Current Program Path: " << std::filesystem::current_path() << '\n';
        throw std::runtime_error("Content folder not found in directory");
	}
}


