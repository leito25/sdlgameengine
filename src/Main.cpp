#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <sol/sol.hpp>
#include <pybind11/pybind11.h>
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
