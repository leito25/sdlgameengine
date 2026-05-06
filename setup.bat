@echo off
echo TwoDEngine Setup Script
echo =====================

REM Check if g++ is installed
where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo WARNING: g++ not found. Attempting to install MinGW-w64...
    call :install_mingw
    if %ERRORLEVEL% NEQ 0 (
        echo ERROR: Failed to install MinGW-w64. Please install it manually.
        goto :error
    )

    REM Check again after installation
    where g++ >nul 2>&1
    if %ERRORLEVEL% NEQ 0 (
        echo ERROR: g++ still not found after installation attempt.
        echo Please restart your terminal or add MinGW to your PATH manually.
        goto :error
    )
)

REM Check if MinGW make is installed
where mingw32-make >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo WARNING: mingw32-make not found. Attempting to install MinGW-w64...
    call :install_mingw
    if %ERRORLEVEL% NEQ 0 (
        echo ERROR: Failed to install MinGW-w64. Please install it manually.
        goto :error
    )

    REM Check again after installation
    where mingw32-make >nul 2>&1
    if %ERRORLEVEL% NEQ 0 (
        echo ERROR: mingw32-make still not found after installation attempt.
        echo Please restart your terminal or add MinGW to your PATH manually.
        goto :error
    )
)

echo MinGW found. Proceeding with setup...

REM Create necessary directories
if not exist bin mkdir bin
echo Created bin directory.

REM Download SDL2 if not already present
if not exist SDL2-2.30.5 (
    echo Downloading SDL2...
    curl -L https://github.com/libsdl-org/SDL/releases/download/release-2.30.5/SDL2-devel-2.30.5-mingw.zip -o SDL2-mingw.zip
    echo Extracting SDL2...
    tar -xf SDL2-mingw.zip
    echo SDL2 downloaded and extracted.
) else (
    echo SDL2 already exists, skipping download.
)

REM Download SDL2_image if not already present
if not exist SDL2_image-2.8.2 (
    echo Downloading SDL2_image...
    curl -L https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-mingw.zip -o SDL2_image-mingw.zip
    echo Extracting SDL2_image...
    tar -xf SDL2_image-mingw.zip
    echo SDL2_image downloaded and extracted.
) else (
    echo SDL2_image already exists, skipping download.
)

REM Download SDL2_ttf if not already present
if not exist SDL2_ttf-2.22.0 (
    echo Downloading SDL2_ttf...
    curl -L https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-mingw.zip -o SDL2_ttf-mingw.zip
    echo Extracting SDL2_ttf...
    tar -xf SDL2_ttf-mingw.zip
    echo SDL2_ttf downloaded and extracted.
) else (
    echo SDL2_ttf already exists, skipping download.
)

REM Download SDL2_mixer if not already present
if not exist SDL2_mixer-2.8.0 (
    echo Downloading SDL2_mixer...
    curl -L https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-mingw.zip -o SDL2_mixer-mingw.zip
    echo Extracting SDL2_mixer...
    tar -xf SDL2_mixer-mingw.zip
    echo SDL2_mixer downloaded and extracted.
) else (
    echo SDL2_mixer already exists, skipping download.
)

REM Download and build Lua if not already present
if not exist lua-5.4.6 (
    echo Downloading Lua...
    curl -L https://www.lua.org/ftp/lua-5.4.6.tar.gz -o lua-5.4.6.tar.gz
    echo Extracting Lua...
    tar -xf lua-5.4.6.tar.gz
    echo Building Lua...
    cd lua-5.4.6
    mingw32-make mingw
    cd ..
    echo Lua downloaded, extracted, and built.
) else (
    echo Lua already exists, skipping download and build.
)

REM Download and set up Python if not already present
if not exist python-3.10.11 (
    echo Downloading Python embedded distribution...
    curl -L https://www.python.org/ftp/python/3.10.11/python-3.10.11-embed-amd64.zip -o python-3.10.11-embed-amd64.zip
    echo Extracting Python...
    mkdir python-3.10.11
    tar -xf python-3.10.11-embed-amd64.zip -C python-3.10.11
    echo Python downloaded and extracted.
) else (
    echo Python already exists, skipping download.
)

REM Download and set up pybind11 if not already present
if not exist pybind11-2.11.1 (
    echo Downloading pybind11...
    curl -L https://github.com/pybind/pybind11/archive/refs/tags/v2.11.1.zip -o pybind11-2.11.1.zip
    echo Extracting pybind11...
    tar -xf pybind11-2.11.1.zip
    echo pybind11 downloaded and extracted.
) else (
    echo pybind11 already exists, skipping download.
)

REM Copy DLLs to bin directory
echo Copying DLLs to bin directory...
copy SDL2-2.30.5\x86_64-w64-mingw32\bin\SDL2.dll bin\
copy SDL2_image-2.8.2\x86_64-w64-mingw32\bin\SDL2_image.dll bin\
copy SDL2_ttf-2.22.0\x86_64-w64-mingw32\bin\SDL2_ttf.dll bin\
copy SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin\SDL2_mixer.dll bin\
copy lua-5.4.6\src\lua54.dll bin\
echo DLLs copied to bin directory.

REM Build the project
echo Building the project...
mingw32-make
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed.
    goto :error
)
echo Project built successfully.

REM Copy DLLs to examples directory
echo Copying DLLs to examples directory...
if not exist examples mkdir examples
copy SDL2-2.30.5\x86_64-w64-mingw32\bin\SDL2.dll examples\
copy SDL2_image-2.8.2\x86_64-w64-mingw32\bin\SDL2_image.dll examples\
copy SDL2_ttf-2.22.0\x86_64-w64-mingw32\bin\SDL2_ttf.dll examples\
copy SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin\SDL2_mixer.dll examples\
copy lua-5.4.6\src\lua54.dll examples\
echo DLLs copied to examples directory.

echo.
echo Setup completed successfully!
echo.
echo You can now run the main application with:
echo   bin\main.exe
echo.
goto :end

:install_mingw
echo.
echo ========================================
echo Installing MinGW-w64 (w64devkit)...
echo ========================================
echo.

REM Create a temporary directory for download
if not exist temp_mingw mkdir temp_mingw
cd temp_mingw

REM Download w64devkit (a portable MinGW-w64 distribution)
echo Downloading w64devkit (MinGW-w64 distribution)...
curl -L https://github.com/skeeto/w64devkit/releases/download/v1.21.0/w64devkit-1.21.0.zip -o w64devkit.zip
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to download w64devkit.
    cd ..
    exit /b 1
)

echo Extracting w64devkit...
tar -xf w64devkit.zip
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to extract w64devkit.
    cd ..
    exit /b 1
)

REM Move w64devkit to a permanent location
cd ..
if exist C:\w64devkit (
    echo w64devkit already exists at C:\w64devkit
) else (
    echo Moving w64devkit to C:\w64devkit...
    move temp_mingw\w64devkit C:\w64devkit
)

REM Add to PATH for current session
echo Adding MinGW to PATH for current session...
set "PATH=C:\w64devkit\bin;%PATH%"

REM Add to system PATH permanently (requires admin rights, may fail)
echo Attempting to add MinGW to system PATH permanently...
setx PATH "C:\w64devkit\bin;%PATH%" >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo MinGW added to system PATH successfully.
) else (
    echo WARNING: Could not add to system PATH permanently (may require admin rights).
    echo You can add C:\w64devkit\bin to your PATH manually or run this script as administrator.
)

REM Clean up
echo Cleaning up temporary files...
rmdir /s /q temp_mingw

echo.
echo MinGW-w64 installation completed!
echo Location: C:\w64devkit
echo.
echo NOTE: If g++ is still not found, please:
echo   1. Restart your terminal/command prompt
echo   2. Or manually add C:\w64devkit\bin to your system PATH
echo.

exit /b 0

:error
echo.
echo Setup failed. Please check the error messages above.
exit /b 1

:end
echo.
echo Thank you for using TwoDEngine!
