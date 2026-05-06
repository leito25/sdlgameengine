@echo off
REM ============================================================================
REM TwoDEngine Documentation Generator
REM ============================================================================
REM This script generates both Doxygen and MkDocs documentation
REM ============================================================================

echo.
echo ========================================
echo  TwoDEngine Documentation Generator
echo ========================================
echo.

REM ============================================================================
REM Generate Doxygen API Documentation
REM ============================================================================

echo [1/2] Generating Doxygen API documentation...
echo.

REM Check if Doxygen is installed
doxygen --version >nul 2>&1
if errorlevel 1 (
    echo [ERROR] Doxygen is not installed or not in PATH
    echo Please install Doxygen from https://www.doxygen.nl/download.html
    pause
    exit /b 1
)

REM Generate Doxygen docs
doxygen Doxyfile
if errorlevel 1 (
    echo [ERROR] Failed to generate Doxygen documentation
    pause
    exit /b 1
)

echo [SUCCESS] Doxygen documentation generated!
echo Location: docs\api\html\index.html
echo.

REM ============================================================================
REM Generate MkDocs User Documentation
REM ============================================================================

echo [2/2] Generating MkDocs user documentation...
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
    pip install mkdocs mkdocs-material
    if errorlevel 1 (
        echo [ERROR] Failed to install MkDocs
        pause
        exit /b 1
    )
    echo [SUCCESS] MkDocs installed!
    echo.
)

REM Build MkDocs site
python -m mkdocs build
if errorlevel 1 (
    echo [ERROR] Failed to generate MkDocs documentation
    pause
    exit /b 1
)

echo [SUCCESS] MkDocs documentation generated!
echo Location: site\index.html
echo.

REM ============================================================================
REM Summary
REM ============================================================================

echo ========================================
echo  Documentation Generation Complete!
echo ========================================
echo.
echo Generated documentation:
echo   1. API Reference (Doxygen):
echo      docs\api\html\index.html
echo.
echo   2. User Guide (MkDocs):
echo      site\index.html
echo.
echo To view documentation:
echo   - Run: serve_docs.bat (for live server)
echo   - Run: view_api_docs.bat (for API docs)
echo   - Or open the HTML files directly
echo.
pause
