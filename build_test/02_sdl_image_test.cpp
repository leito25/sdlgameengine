#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::cout << "✓ SDL2 initialized successfully!" << std::endl;
    std::cout << "✓ SDL_image initialized successfully!" << std::endl;

    SDL_version compile_version;
    const SDL_version *link_version = IMG_Linked_Version();
    SDL_IMAGE_VERSION(&compile_version);
    std::cout << "SDL_image Version: " << (int)link_version->major << "."
              << (int)link_version->minor << "." << (int)link_version->patch << std::endl;

    IMG_Quit();
    SDL_Quit();
    return 0;
}
