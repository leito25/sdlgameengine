@echo off
setlocal

set BUILD_TYPE=debug

if "%1"=="release" (
    set BUILD_TYPE=release
)

if "%BUILD_TYPE%"=="debug" (
    echo Building TwoDEngine in debug mode...
    mingw32-make
) else (
    echo Building TwoDEngine in release mode...
    mingw32-make CXXFLAGS="-std=c++17 -O3 -DNDEBUG -Isrc -Ipybind11-2.11.1/include -IC:/Python314/include -Ilibs -Ilibs/glm -Ilibs/imgui -Ilibs/lua -Ilibs/sol -Ilua-5.4.6/src -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2"
)

if %ERRORLEVEL% neq 0 (
    echo Error building the engine.
    pause
    exit /b %ERRORLEVEL%
)

echo Copying required DLLs...
copy /Y SDL2-2.30.5\x86_64-w64-mingw32\bin\SDL2.dll bin\ >nul 2>&1
copy /Y SDL2_image-2.8.2\x86_64-w64-mingw32\bin\SDL2_image.dll bin\ >nul 2>&1
copy /Y SDL2_ttf-2.22.0\x86_64-w64-mingw32\bin\SDL2_ttf.dll bin\ >nul 2>&1
copy /Y SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin\SDL2_mixer.dll bin\ >nul 2>&1
copy /Y lua-5.4.6\src\lua54.dll bin\ >nul 2>&1
copy /Y C:\Python314\python3.dll bin\ >nul 2>&1
copy /Y C:\Python314\python314.dll bin\ >nul 2>&1
copy /Y C:\Python314\vcruntime140.dll bin\ >nul 2>&1
copy /Y C:\Python314\vcruntime140_1.dll bin\ >nul 2>&1

echo Running TwoDEngine...
bin\main.exe

echo Engine execution completed.
pause
