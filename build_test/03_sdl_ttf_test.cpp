#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::cout << "✓ SDL2 initialized successfully!" << std::endl;
    std::cout << "✓ SDL_ttf initialized successfully!" << std::endl;

    SDL_version compile_version;
    const SDL_version *link_version = TTF_Linked_Version();
    SDL_TTF_VERSION(&compile_version);
    std::cout << "SDL_ttf Version: " << (int)link_version->major << "."
              << (int)link_version->minor << "." << (int)link_version->patch << std::endl;

    TTF_Quit();
    SDL_Quit();
    return 0;
}
