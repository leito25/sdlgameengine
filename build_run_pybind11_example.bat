@echo off
echo Building and Running Pybind11 Example
echo ====================================

REM Build the project
echo Building the project...
g++ -std=c++17 -Isrc -Ilibs -Ilibs/glm -Ilibs/imgui -Ilibs/lua -Ilibs/python -Ilua-5.4.6/src -Ipython-3.10.11/include -Ipybind11-2.11.1/include -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2 -c examples/Pybind11Example.cpp -o examples/Pybind11Example.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed.
    goto :error
)

g++ examples/Pybind11Example.o -o bin/Pybind11Example.exe -LSDL2-2.30.5/x86_64-w64-mingw32/lib -LSDL2_image-2.8.2/x86_64-w64-mingw32/lib -LSDL2_ttf-2.22.0/x86_64-w64-mingw32/lib -LSDL2_mixer-2.8.0/x86_64-w64-mingw32/lib -Llua-5.4.6/src -Lpython-3.10.11/libs -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua -lpython310
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Link failed.
    goto :error
)

echo Project built successfully.

REM Copy Python script to bin directory
echo Copying Python script to bin directory...
if not exist bin\assets\scripts mkdir bin\assets\scripts
copy assets\scripts\pybind11_data_processor.py bin\assets\scripts\
echo Python script copied to bin directory.

REM Copy DLLs to bin directory
echo Copying DLLs to bin directory...
copy SDL2-2.30.5\x86_64-w64-mingw32\bin\SDL2.dll bin\
copy SDL2_image-2.8.2\x86_64-w64-mingw32\bin\SDL2_image.dll bin\
copy SDL2_ttf-2.22.0\x86_64-w64-mingw32\bin\SDL2_ttf.dll bin\
copy SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin\SDL2_mixer.dll bin\
copy lua-5.4.6\src\lua54.dll bin\
copy python-3.10.11\*.dll bin\
echo DLLs copied to bin directory.

REM Run the example
echo Running Pybind11 Example...
cd bin
Pybind11Example.exe
cd ..

goto :end

:error
echo.
echo Build or run failed. Please check the error messages above.
exit /b 1

:end
echo.
echo Pybind11 example completed successfully!
