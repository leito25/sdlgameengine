@echo off
echo Testing Python Integration for TwoDEngine
echo =======================================

REM Check if the Python binding header exists
if not exist libs\python\PythonBinding.h (
    echo ERROR: Python binding header not found.
    goto :error
)

REM Check if the Python script exists
if not exist assets\scripts\main.py (
    echo ERROR: Python script not found.
    goto :error
)

REM Check if the Python DLLs exist
if not exist python-3.10.11\_asyncio.pyd (
    echo ERROR: Python DLLs not found.
    goto :error
)

REM Check if pybind11 exists
if not exist pybind11-2.11.1\include\pybind11\pybind11.h (
    echo ERROR: pybind11 not found.
    goto :error
)

REM Check if Main.cpp includes Python
findstr /C:"#include <python/PythonBinding.h>" src\Main.cpp >nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Main.cpp does not include Python binding header.
    goto :error
)

REM Check if CMakeLists.txt includes Python
findstr /C:"PYTHON_PATH" CMakeLists.txt >nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMakeLists.txt does not include Python path.
    goto :error
)

REM Check if setup.bat includes Python
findstr /C:"python-3.10.11" setup.bat >nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: setup.bat does not include Python setup.
    goto :error
)

echo All Python integration components are in place!
echo.
echo To fully test the integration, build and run the engine:
echo   mingw32-make
echo   bin\main.exe
echo.
echo If the engine starts without errors and displays "Python initialized successfully!"
echo in the console, the integration is working correctly.
echo.
goto :end

:error
echo.
echo Python integration test failed. Please check the error messages above.
exit /b 1

:end
echo.
echo Python integration test completed successfully!
