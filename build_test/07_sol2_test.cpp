#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    lua.script("result = 2 + 2");
    int result = lua["result"];

    std::cout << "✓ Lua initialized successfully!" << std::endl;
    std::cout << "✓ Sol2 is working!" << std::endl;
    std::cout << "Lua computed: 2 + 2 = " << result << std::endl;

    return 0;
}
