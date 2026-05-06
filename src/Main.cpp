#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <sol/sol.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {
    // Initialize Lua
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    // Use GLM
    glm::vec3 velocity = glm::vec3(1.0f, 2.0f, 3.0f);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_Image
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_TTF
    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "TwoDEngine with SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGuiSDL::Initialize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Main loop
    bool running = true;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            // Process ImGui events manually
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
                running = false;
            if (event.type == SDL_MOUSEMOTION) {
                io.MousePos = ImVec2(event.motion.x, event.motion.y);
            } else if (event.type == SDL_MOUSEWHEEL) {
                io.MouseWheel = event.wheel.y;
            } else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                int button = event.button.button - 1;
                if (button >= 0 && button < 3) {
                    io.MouseDown[button] = (event.type == SDL_MOUSEBUTTONDOWN);
                }
            } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                io.KeysDown[event.key.keysym.scancode] = (event.type == SDL_KEYDOWN);
                io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
                io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
                io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
            } else if (event.type == SDL_TEXTINPUT) {
                io.AddInputCharactersUTF8(event.text.text);
            }
        }

        // Start ImGui frame
        ImGui::NewFrame();

        // Create ImGui window
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a basic SDL2 window with ImGui integration");
        ImGui::Text("GLM vector: (%.1f, %.1f, %.1f)", velocity.x, velocity.y, velocity.z);
        ImGui::Text("Lua and Sol2 are also integrated");
        if (ImGui::Button("Quit")) {
            running = false;
        }
        ImGui::End();

        // Render
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // Cornflower blue
        SDL_RenderClear(renderer);

        // Render ImGui
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);

        // Cap to 60 FPS
        SDL_Delay(1000 / 60);
    }

    // Cleanup
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    std::cout << "SDL application closed successfully!" << std::endl;
    // Python will be cleaned up when the PythonBinding object goes out of scope

    return 0;
}
