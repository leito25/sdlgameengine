@echo off
REM ============================================================================
REM TwoDEngine Documentation Server
REM ============================================================================
REM This script starts the MkDocs development server to view documentation
REM ============================================================================

echo.
echo ========================================
echo  TwoDEngine Documentation Server
echo ========================================
echo.

REM Check if Python is installed
python --version >nul 2>&1
if errorlevel 1 (
    echo [ERROR] Python is not installed or not in PATH
    echo Please install Python 3.7+ from https://www.python.org/
    pause
    exit /b 1
)

REM Check if MkDocs is installed
python -m mkdocs --version >nul 2>&1
if errorlevel 1 (
    echo [INFO] MkDocs is not installed. Installing now...
    echo.
    pip install mkdocs mkdocs-material
    if errorlevel 1 (
        echo [ERROR] Failed to install MkDocs
        pause
        exit /b 1
    )
    echo.
    echo [SUCCESS] MkDocs installed successfully!
    echo.
)

echo [INFO] Starting MkDocs development server...
echo.
echo ========================================
echo  Documentation will be available at:
echo  http://127.0.0.1:8000/TwoDEngine/
echo ========================================
echo.
echo Press Ctrl+C to stop the server
echo.

REM Start MkDocs server
python -m mkdocs serve

REM If server stops
echo.
echo [INFO] Documentation server stopped.
pause
