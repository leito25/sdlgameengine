@echo off
setlocal

set BUILD_TYPE=release
set DIST_DIR=dist

if "%1"=="debug" (
    set BUILD_TYPE=debug
    set DIST_DIR=dist-debug
)

echo ========================================
echo Packaging TwoDEngine (%BUILD_TYPE%)
echo ========================================

REM Build the engine
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

REM Clean and create distribution directory
echo Cleaning old distribution directory...
if exist %DIST_DIR% rmdir /s /q %DIST_DIR%
mkdir %DIST_DIR%

REM Copy executable
echo Copying executable...
copy bin\main.exe %DIST_DIR%\

REM Copy SDL2 DLLs
echo Copying SDL2 DLLs...
copy SDL2-2.30.5\x86_64-w64-mingw32\bin\SDL2.dll %DIST_DIR%\
copy SDL2_image-2.8.2\x86_64-w64-mingw32\bin\*.dll %DIST_DIR%\
copy SDL2_ttf-2.22.0\x86_64-w64-mingw32\bin\*.dll %DIST_DIR%\
copy SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin\*.dll %DIST_DIR%\

REM Copy assets
echo Copying assets...
xcopy /E /I /Y assets %DIST_DIR%\assets

REM Copy README and LICENSE if they exist
if exist README.md copy README.md %DIST_DIR%\
if exist LICENSE copy LICENSE %DIST_DIR%\

echo ========================================
echo Package created successfully in %DIST_DIR%\
echo ========================================
echo.
echo You can now distribute the contents of the %DIST_DIR% directory.
