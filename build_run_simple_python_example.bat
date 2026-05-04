@echo off
echo Building and Running Simple Python Example
echo =========================================

REM Create bin directory if it doesn't exist
if not exist bin mkdir bin

REM Build the project
echo Building the project...
g++ -std=c++17 -o bin/SimplePythonExample.exe examples/SimplePythonExample.cpp
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed.
    goto :error
)

echo Project built successfully.

REM Copy Python script to bin directory
echo Copying Python script to bin directory...
if not exist bin\assets\scripts mkdir bin\assets\scripts
copy assets\scripts\simple_python_example.py bin\assets\scripts\
echo Python script copied to bin directory.

REM Copy DLLs to bin directory
echo Copying DLLs to bin directory...
copy python-3.10.11\python310.dll bin\
copy python-3.10.11\python3.dll bin\
copy python-3.10.11\vcruntime140.dll bin\
copy python-3.10.11\vcruntime140_1.dll bin\
echo DLLs copied to bin directory.

REM Run the example
echo Running Simple Python Example...
cd bin
SimplePythonExample.exe
cd ..

goto :end

:error
echo.
echo Build or run failed. Please check the error messages above.
exit /b 1

:end
echo.
echo Simple Python example completed successfully!
