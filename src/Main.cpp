#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>      // ✓ Installed
#include <SDL_ttf.h>        // ✓ Installed
#include <SDL_mixer.h>      // ✓ Installed
#include <glm/glm.hpp>      // ✓ Installed
#include <imgui.h>          // ✓ Installed (external/imgui)
#include <imgui_impl_sdl2.h>
#include <sol/sol.hpp>      // ✓ Installed (external/sol2)
#include <pybind11/pybind11.h>  // ✓ Installed
#include <pybind11/embed.h>

#include "Game.h"


int main(int argc, char* argv[])
{
    // class that handle the game loop and all the game logic
    Game game;

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}
