@echo off
setlocal

set BUILD_TYPE=debug

if "%1"=="release" (
    set BUILD_TYPE=release
)

echo Building TwoDEngine in %BUILD_TYPE% mode...
mingw32-make BUILD_TYPE=%BUILD_TYPE%

if %ERRORLEVEL% neq 0 (
    echo Error: build failed.
    exit /b %ERRORLEVEL%
)

echo Running TwoDEngine...
bin\main.exe

echo Engine execution completed.
