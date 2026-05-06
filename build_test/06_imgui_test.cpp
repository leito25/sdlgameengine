#include <SDL.h>
#include "imgui.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    std::cout << "✓ SDL2 initialized successfully!" << std::endl;
    std::cout << "✓ ImGui initialized successfully!" << std::endl;
    std::cout << "ImGui Version: " << IMGUI_VERSION << std::endl;

    ImGui::DestroyContext();
    SDL_Quit();
    return 0;
}
