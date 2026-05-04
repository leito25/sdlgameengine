@echo off
echo Building and Running Python Game Example
echo =======================================

REM Build the project
echo Building the project...
mingw32-make PythonGame
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed.
    goto :error
)
echo Project built successfully.

REM Copy assets to bin directory
echo Copying assets to bin directory...
if not exist bin\assets mkdir bin\assets
if not exist bin\assets\fonts mkdir bin\assets\fonts
if not exist bin\assets\images mkdir bin\assets\images
if not exist bin\assets\sounds mkdir bin\assets\sounds
if not exist bin\assets\scripts mkdir bin\assets\scripts
xcopy /Y /Q assets\fonts\*.* bin\assets\fonts\
xcopy /Y /Q assets\images\*.* bin\assets\images\
xcopy /Y /Q assets\sounds\*.* bin\assets\sounds\
xcopy /Y /Q assets\scripts\*.* bin\assets\scripts\
echo Assets copied to bin directory.

REM Copy DLLs to bin directory
echo Copying DLLs to bin directory...
copy SDL2-2.30.5\x86_64-w64-mingw32\bin\SDL2.dll bin\
copy SDL2_image-2.8.2\x86_64-w64-mingw32\bin\SDL2_image.dll bin\
copy SDL2_ttf-2.22.0\x86_64-w64-mingw32\bin\SDL2_ttf.dll bin\
copy SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin\SDL2_mixer.dll bin\
copy lua-5.4.6\src\lua54.dll bin\
copy python-3.10.11\*.dll bin\
echo DLLs copied to bin directory.

REM Run the Python game
echo Running Python Game...
cd bin
PythonGame.exe
cd ..

goto :end

:error
echo.
echo Build or run failed. Please check the error messages above.
exit /b 1

:end
echo.
echo Python Game example completed successfully!
