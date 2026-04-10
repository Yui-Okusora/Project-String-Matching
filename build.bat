@echo off
SETLOCAL
SET BUILD_DIR=build
SET EXE_NAME=01.exe
SET STACK_SIZE=32000000

echo [INFO] Starting build process for Project-Sort...

where cmake >nul 2>nul
if %errorlevel% equ 0 (
    echo [INFO] CMake found. Using CMake to build...
    if not exist %BUILD_DIR% mkdir %BUILD_DIR%
    cd %BUILD_DIR%
    cmake ..
    cmake --build . --config Release
    
    if %errorlevel% equ 0 (
        if exist Release\%EXE_NAME% copy Release\%EXE_NAME% ..\%EXE_NAME% >nul
        if exist %EXE_NAME% copy %EXE_NAME% ..\%EXE_NAME% >nul
        echo [SUCCESS] Build completed via CMake.
        goto :finish
    )
    echo [WARN] CMake build failed. Trying direct g++...
    cd ..
)

where g++ >nul 2>nul
if %errorlevel% equ 0 (
    echo [INFO] Compiling directly with g++...
    g++ src/*.cpp -std=c++17 -Wl,--stack,%STACK_SIZE% -o %EXE_NAME%
    
    if %errorlevel% equ 0 (
        echo [SUCCESS] Build completed via g++.
        goto :finish
    )
)

echo [ERROR] No suitable compiler found or compilation failed.
pause
exit /b 1

:finish
echo [INFO] Executable is ready: %EXE_NAME%
echo [INFO] You can now run commands like: %EXE_NAME% -a radix-sort input.txt -both
pause
