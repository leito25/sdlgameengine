#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <sol/sol.hpp>
#include <python/PythonBinding.h>

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "SDL initialized successfully!" << std::endl;

    glm::vec2 velocity = glm::vec2(1.0f, 2.0f);
    std::cout << "Velocity: (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")" << std::endl;

    return 0;
}
