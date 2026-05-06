@echo off
setlocal

set BUILD_TYPE=debug

if "%1"=="release" (
    set BUILD_TYPE=release
)

if "%BUILD_TYPE%"=="debug" (
    echo Building TwoDEngine in debug mode...
    mingw32-make CXXFLAGS="-std=c++17 -g -Isrc -Ilibs -Ilibs/glm -Ilibs/imgui -Ilibs/lua -Ilua-5.4.6/src -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2"
) else (
    echo Building TwoDEngine in release mode...
    mingw32-make CXXFLAGS="-std=c++17 -O3 -DNDEBUG -Isrc -Ilibs -Ilibs/glm -Ilibs/imgui -Ilibs/lua -Ilua-5.4.6/src -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2"
)

if %ERRORLEVEL% neq 0 (
    echo Error building the engine.
    exit /b %ERRORLEVEL%
)

echo Running TwoDEngine...
bin\main.exe

echo Engine execution completed.
