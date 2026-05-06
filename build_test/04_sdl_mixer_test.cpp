#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::cout << "✓ SDL2 initialized successfully!" << std::endl;
    std::cout << "✓ SDL_mixer initialized successfully!" << std::endl;

    SDL_version compile_version;
    const SDL_version *link_version = Mix_Linked_Version();
    SDL_MIXER_VERSION(&compile_version);
    std::cout << "SDL_mixer Version: " << (int)link_version->major << "."
              << (int)link_version->minor << "." << (int)link_version->patch << std::endl;

    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}
