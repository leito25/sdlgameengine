:: This is also a comment This is a batch script to compile the mian.cpp file using g++
:: This is also a commentg++ mian.cpp -o mian.exe

:: This is also a comment Now  I'll add some flags
:: g++ main.cpp -o mian.exe -Wall -Wextra -std=c++17
:: This is also a comment -Wall add all warnings,
:: This is also a comment -Wextra adds extra warnings, and
:: This is also a comment -std=c++17 specifies that we want to use the C++17 standard.

::-Wextra
g++ main.cpp -o mian.exe -Wall -std=c++17 -I../../SDL2-2.30.5/x86_64-w64-mingw32/include/SDL2
