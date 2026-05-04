@echo off
setlocal

set BUILD_TYPE=release
set DIST_DIR=dist-python

if "%1"=="debug" (
    set BUILD_TYPE=debug
    set DIST_DIR=dist-python-debug
)

echo Packaging Python Game in %BUILD_TYPE% mode...

echo Creating distribution directory...
mkdir %DIST_DIR% 2>nul

echo Building Python Game in %BUILD_TYPE% mode...

if "%BUILD_TYPE%"=="debug" (
    mingw32-make PythonGame CXXFLAGS="-std=c++17 -g -Isrc -Ilibs -Ilibs/glm -Ilibs/imgui -Ilibs/lua -Ilibs/python -Ilua-5.4.6/src -Ipython-3.10.11 -Ipybind11-2.11.1/include -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2"
) else (
    mingw32-make PythonGame CXXFLAGS="-std=c++17 -O3 -DNDEBUG -Isrc -Ilibs -Ilibs/glm -Ilibs/imgui -Ilibs/lua -Ilibs/python -Ilua-5.4.6/src -Ipython-3.10.11 -Ipybind11-2.11.1/include -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2"
)

if %ERRORLEVEL% neq 0 (
    echo Error building the Python game.
    pause
    exit /b %ERRORLEVEL%
)

echo Copying executable to distribution directory...
copy bin\PythonGame.exe %DIST_DIR%\

echo Copying DLLs to distribution directory...
copy SDL2-2.30.5\x86_64-w64-mingw32\bin\*.dll %DIST_DIR%\ 2>nul
copy SDL2_image-2.8.2\x86_64-w64-mingw32\bin\*.dll %DIST_DIR%\ 2>nul
copy SDL2_ttf-2.22.0\x86_64-w64-mingw32\bin\*.dll %DIST_DIR%\ 2>nul
copy SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin\*.dll %DIST_DIR%\ 2>nul

echo Copying Python DLLs to distribution directory...
copy python-3.10.11\*.pyd %DIST_DIR%\ 2>nul
copy python-3.10.11\*.dll %DIST_DIR%\ 2>nul

echo Copying assets to distribution directory...
mkdir %DIST_DIR%\assets 2>nul
xcopy /E /I /Y assets %DIST_DIR%\assets

if "%BUILD_TYPE%"=="debug" (
    echo Python game has been packaged to the 'dist-python-debug' directory.
    echo This debug build includes debugging symbols for development and testing.
) else (
    echo Python game has been packaged to the 'dist-python' directory.
    echo This release build is optimized for distribution to users.
)

pause
