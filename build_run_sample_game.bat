@echo off
setlocal

set BUILD_TYPE=debug

if "%1"=="release" (
    set BUILD_TYPE=release
)

echo Building Sample Game in %BUILD_TYPE% mode...
cd examples

if "%BUILD_TYPE%"=="debug" (
    mingw32-make CXXFLAGS="-std=c++17 -g -I../src -I../libs -I../libs/glm -I../libs/imgui -I../libs/lua -I../lua-5.4.6/src -I../SDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 -I../SDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 -I../SDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 -I../SDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2"
) else (
    mingw32-make CXXFLAGS="-std=c++17 -O3 -DNDEBUG -I../src -I../libs -I../libs/glm -I../libs/imgui -I../libs/lua -I../lua-5.4.6/src -I../SDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 -I../SDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 -I../SDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 -I../SDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2"
)

if %ERRORLEVEL% neq 0 (
    echo Error building the sample game.
    cd ..
    pause
    exit /b %ERRORLEVEL%
)

echo Running Sample Game...
SimpleGame.exe
cd ..

echo Sample game execution completed.
pause
