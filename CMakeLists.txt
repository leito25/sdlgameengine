cmake_minimum_required(VERSION 3.10)
project(TwoDEngine VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(BUILD_EXAMPLES "Build the example applications" ON)

# Define paths for SDL2 and other libraries
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/SDL2-2.30.5/x86_64-w64-mingw32" CACHE PATH "Path to SDL2")
set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/SDL2_image-2.8.2/x86_64-w64-mingw32" CACHE PATH "Path to SDL2_image")
set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/SDL2_ttf-2.22.0/x86_64-w64-mingw32" CACHE PATH "Path to SDL2_ttf")
set(SDL2_MIXER_PATH "${CMAKE_SOURCE_DIR}/SDL2_mixer-2.8.0/x86_64-w64-mingw32" CACHE PATH "Path to SDL2_mixer")
set(LUA_PATH "${CMAKE_SOURCE_DIR}/lua-5.4.6" CACHE PATH "Path to Lua")
set(PYTHON_PATH "${CMAKE_SOURCE_DIR}/python-3.10.11" CACHE PATH "Path to Python")
set(PYBIND11_PATH "${CMAKE_SOURCE_DIR}/pybind11-2.11.1" CACHE PATH "Path to pybind11")

# Include directories
include_directories(
    ${SDL2_PATH}/include/SDL2
    ${SDL2_IMAGE_PATH}/include/SDL2
    ${SDL2_TTF_PATH}/include/SDL2
    ${SDL2_MIXER_PATH}/include/SDL2
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/libs
    ${CMAKE_SOURCE_DIR}/libs/glm
    ${CMAKE_SOURCE_DIR}/libs/imgui
    ${CMAKE_SOURCE_DIR}/libs/lua
    ${CMAKE_SOURCE_DIR}/libs/python
    ${LUA_PATH}/src
    ${PYTHON_PATH}
    ${PYBIND11_PATH}/include
)

# Link directories
link_directories(
    ${SDL2_PATH}/lib
    ${SDL2_IMAGE_PATH}/lib
    ${SDL2_TTF_PATH}/lib
    ${SDL2_MIXER_PATH}/lib
    ${LUA_PATH}/src
    ${PYTHON_PATH}
)

# ImGui source files
set(IMGUI_SOURCES
    libs/imgui/imgui.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/imgui_demo.cpp
    libs/imgui/imgui_sdl.cpp
)

# Main executable
add_executable(TwoDEngine
    src/Main.cpp
    ${IMGUI_SOURCES}
)

# Link libraries
target_link_libraries(TwoDEngine
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    lua
)

# Build examples
if(BUILD_EXAMPLES)
    # SimpleGame example
    add_executable(SimpleGame
        examples/SimpleGame.cpp
        ${IMGUI_SOURCES}
    )

    target_link_libraries(SimpleGame
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        lua
    )

    # PythonGame example
    add_executable(PythonGame
        examples/PythonGame.cpp
        ${IMGUI_SOURCES}
    )

    target_link_libraries(PythonGame
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
    )
endif()

# Installation
install(TARGETS TwoDEngine DESTINATION bin)
if(BUILD_EXAMPLES)
    install(TARGETS SimpleGame DESTINATION bin)
endif()

# Copy DLLs for Windows
if(WIN32)
    # Helper function to copy DLLs
    function(copy_dll target dll_path)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${dll_path}"
            $<TARGET_FILE_DIR:${target}>
        )
    endfunction()

    # Copy SDL2 DLLs
    copy_dll(TwoDEngine "${SDL2_PATH}/bin/SDL2.dll")
    copy_dll(TwoDEngine "${SDL2_IMAGE_PATH}/bin/SDL2_image.dll")
    copy_dll(TwoDEngine "${SDL2_TTF_PATH}/bin/SDL2_ttf.dll")
    copy_dll(TwoDEngine "${SDL2_MIXER_PATH}/bin/SDL2_mixer.dll")
    copy_dll(TwoDEngine "${LUA_PATH}/src/lua54.dll")

    if(BUILD_EXAMPLES)
        copy_dll(SimpleGame "${SDL2_PATH}/bin/SDL2.dll")
        copy_dll(SimpleGame "${SDL2_IMAGE_PATH}/bin/SDL2_image.dll")
        copy_dll(SimpleGame "${SDL2_TTF_PATH}/bin/SDL2_ttf.dll")
        copy_dll(SimpleGame "${SDL2_MIXER_PATH}/bin/SDL2_mixer.dll")
        copy_dll(SimpleGame "${LUA_PATH}/src/lua54.dll")

        copy_dll(PythonGame "${SDL2_PATH}/bin/SDL2.dll")
        copy_dll(PythonGame "${SDL2_IMAGE_PATH}/bin/SDL2_image.dll")
        copy_dll(PythonGame "${SDL2_TTF_PATH}/bin/SDL2_ttf.dll")
        copy_dll(PythonGame "${SDL2_MIXER_PATH}/bin/SDL2_mixer.dll")

        # Copy Python DLLs
        file(GLOB PYTHON_DLLS "${PYTHON_PATH}/*.pyd" "${PYTHON_PATH}/*.dll")
        foreach(PYTHON_DLL ${PYTHON_DLLS})
            copy_dll(PythonGame "${PYTHON_DLL}")
        endforeach()
    endif()
endif()

# Create bin directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Output information
message(STATUS "TwoDEngine configuration:")
message(STATUS "  SDL2 path: ${SDL2_PATH}")
message(STATUS "  SDL2_image path: ${SDL2_IMAGE_PATH}")
message(STATUS "  SDL2_ttf path: ${SDL2_TTF_PATH}")
message(STATUS "  SDL2_mixer path: ${SDL2_MIXER_PATH}")
message(STATUS "  Lua path: ${LUA_PATH}")
message(STATUS "  Building examples: ${BUILD_EXAMPLES}")
