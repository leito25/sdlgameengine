@echo off
setlocal

set BUILD_TYPE=release
set DIST_DIR=dist

if "%1"=="debug" (
    set BUILD_TYPE=debug
    set DIST_DIR=dist-debug
)

echo Packaging Sample Game in %BUILD_TYPE% mode...

echo Creating distribution directory...
mkdir %DIST_DIR% 2>nul

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

echo Copying executable to distribution directory...
copy SimpleGame.exe ..\%DIST_DIR%\

echo Copying DLLs to distribution directory...
copy *.dll ..\%DIST_DIR%\ 2>nul
copy ..\SDL2-2.30.5\x86_64-w64-mingw32\bin\*.dll ..\%DIST_DIR%\ 2>nul
copy ..\SDL2_image-2.8.2\x86_64-w64-mingw32\bin\*.dll ..\%DIST_DIR%\ 2>nul
copy ..\SDL2_ttf-2.22.0\x86_64-w64-mingw32\bin\*.dll ..\%DIST_DIR%\ 2>nul
copy ..\SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin\*.dll ..\%DIST_DIR%\ 2>nul

cd ..

echo Copying assets to distribution directory...
mkdir %DIST_DIR%\assets 2>nul
xcopy /E /I /Y assets %DIST_DIR%\assets

if "%BUILD_TYPE%"=="debug" (
    echo Sample game has been packaged to the 'dist-debug' directory.
    echo This debug build includes debugging symbols for development and testing.
) else (
    echo Sample game has been packaged to the 'dist' directory.
    echo This release build is optimized for distribution to users.
)

pause
