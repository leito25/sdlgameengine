@echo off
echo TwoDEngine CMake Setup Script
echo ============================

REM Check if CMake is installed
where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: cmake not found. Please install CMake and add it to your PATH.
    goto :error
)

REM Check if MinGW is installed
where mingw32-make >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: mingw32-make not found. Please install MinGW-w64 and add it to your PATH.
    goto :error
)

where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: g++ not found. Please install MinGW-w64 and add it to your PATH.
    goto :error
)

echo CMake and MinGW found. Proceeding with setup...

REM Run the regular setup script to download dependencies
call setup.bat
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to run setup.bat
    goto :error
)

REM Create build directory
if not exist build mkdir build
echo Created build directory.

REM Configure with CMake
echo Configuring with CMake...
cd build
cmake -G "MinGW Makefiles" ..
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake configuration failed.
    cd ..
    goto :error
)

REM Build with CMake
echo Building with CMake...
cmake --build .
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake build failed.
    cd ..
    goto :error
)

cd ..

echo.
echo CMake setup completed successfully!
echo.
echo You can now run the main application with:
echo   build\TwoDEngine.exe
echo.
echo Or run the examples with:
echo   build\SimpleGame.exe
echo.
goto :end

:error
echo.
echo CMake setup failed. Please check the error messages above.
exit /b 1

:end
echo.
echo Thank you for using TwoDEngine!