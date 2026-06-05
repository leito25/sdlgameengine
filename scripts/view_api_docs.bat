@echo off
REM ============================================================================
REM TwoDEngine API Documentation Viewer
REM ============================================================================
REM This script generates (if needed) and opens the Doxygen API documentation
REM ============================================================================

echo.
echo ========================================
echo  TwoDEngine API Documentation
echo ========================================
echo.

REM Check if Doxygen HTML exists
if not exist "docs\api\html\index.html" (
    echo [INFO] API documentation not found. Generating now...
    echo.

    REM Check if Doxygen is installed
    doxygen --version >nul 2>&1
    if errorlevel 1 (
        echo [ERROR] Doxygen is not installed or not in PATH
        echo Please install Doxygen from https://www.doxygen.nl/download.html
        pause
        exit /b 1
    )

    REM Generate documentation
    echo [INFO] Running Doxygen...
    doxygen Doxyfile
    if errorlevel 1 (
        echo [ERROR] Failed to generate documentation
        pause
        exit /b 1
    )
    echo.
    echo [SUCCESS] API documentation generated successfully!
    echo.
)

REM Open documentation in default browser
echo [INFO] Opening API documentation in browser...
start docs\api\html\index.html

echo.
echo [SUCCESS] API documentation opened!
echo Location: docs\api\html\index.html
echo.
pause
