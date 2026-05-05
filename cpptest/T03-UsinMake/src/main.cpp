#include <iostream>
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

namespace py = pybind11;

int main()
{
    std::cout << "=== Testing All Libraries ===" << std::endl << std::endl;

    // Test SDL2
    std::cout << "1. Testing SDL2..." << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cout << "   ✓ SDL initialized successfully!" << std::endl;
        SDL_Quit();
    } else {
        std::cout << "   ✗ SDL initialization failed!" << std::endl;
    }

    // Test GLM
    std::cout << "\n2. Testing GLM..." << std::endl;
    glm::vec2 velocity = glm::vec2(1.0f, 2.0f);
    std::cout << "   ✓ GLM Vector created: (" << velocity.x << ", " << velocity.y << ")" << std::endl;

    // Test Sol2 (Lua)
    std::cout << "\n3. Testing Sol2 (Lua)..." << std::endl;
    try {
        sol::state lua;
        lua.open_libraries(sol::lib::base);
        lua.script("result = 5 + 3");
        int result = lua["result"];
        std::cout << "   ✓ Lua script executed: 5 + 3 = " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "   ✗ Lua error: " << e.what() << std::endl;
    }

    // Test Pybind11 (Python Embedding)
    std::cout << "\n4. Testing Pybind11 (Python)..." << std::endl;
    try {
        // Start the Python interpreter
        py::scoped_interpreter guard{};

        // Execute simple Python code
        py::exec("x = 5 * 7");
        py::exec("print('Hello from Python!')");

        // Get result from Python
        py::object x = py::globals()["x"];
        std::cout << "   ✓ Python executed: 5 * 7 = " << x.cast<int>() << std::endl;

        // Import and use Python modules
        py::module_ sys = py::module_::import("sys");
        py::str version = sys.attr("version");
        std::string version_str = version.cast<std::string>();
        std::cout << "   ✓ Python version: " << version_str.substr(0, version_str.find('\n')) << std::endl;

        // Execute more complex Python code
        py::exec(R"(
def add(a, b):
    return a + b

result = add(10, 20)
)");
        py::object result = py::globals()["result"];
        std::cout << "   ✓ Python function call: add(10, 20) = " << result.cast<int>() << std::endl;

    } catch (const std::exception& e) {
        std::cout << "   ✗ Python error: " << e.what() << std::endl;
    }

    // Test ImGui
    std::cout << "\n5. Testing ImGui..." << std::endl;
    ImGuiContext* ctx = ImGui::CreateContext();
    if (ctx) {
        std::cout << "   ✓ ImGui context created successfully!" << std::endl;
        ImGui::DestroyContext(ctx);
    } else {
        std::cout << "   ✗ ImGui context creation failed!" << std::endl;
    }

    std::cout << "\n=== All Tests Completed ===" << std::endl;

    return 0;
}
