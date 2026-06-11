SHELL       = cmd.exe
.SHELLFLAGS = /C

CXX        = g++
BUILD_TYPE ?= debug
MINGW_BIN  = C:\Strawberry\c\bin

ifeq ($(BUILD_TYPE),release)
    OPT_FLAGS = -O3 -DNDEBUG
else
    OPT_FLAGS = -g
endif

CXXFLAGS = -std=c++17 $(OPT_FLAGS) \
           -Isrc \
           -Iexternal/pybind11/include \
           -IC:/Python314/include \
           -Ilibs -Ilibs/glm -Ilibs/imgui -Ilibs/lua -Ilibs/sol \
           -Iexternal/SDL2/x86_64-w64-mingw32/include \
           -Iexternal/SDL2/x86_64-w64-mingw32/include/SDL2 \
           -Iexternal/SDL2_image/x86_64-w64-mingw32/include \
           -Iexternal/SDL2_image/x86_64-w64-mingw32/include/SDL2 \
           -Iexternal/SDL2_ttf/x86_64-w64-mingw32/include/SDL2 \
           -Iexternal/SDL2_mixer/x86_64-w64-mingw32/include/SDL2 \
           -Iexternal/lua/src

LDFLAGS  = -Lexternal/SDL2/x86_64-w64-mingw32/lib \
           -Lexternal/SDL2_image/x86_64-w64-mingw32/lib \
           -Lexternal/SDL2_ttf/x86_64-w64-mingw32/lib \
           -Lexternal/SDL2_mixer/x86_64-w64-mingw32/lib \
           -Lexternal/lua/src \
           -LC:/Python314/libs \
           -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua -lpython314

SRC_FILES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

SRC = $(SRC_FILES) \
      libs/imgui/imgui.cpp \
      libs/imgui/imgui_draw.cpp \
      libs/imgui/imgui_widgets.cpp \
      libs/imgui/imgui_demo.cpp \
      libs/imgui/imgui_sdl.cpp

OBJ     = $(SRC:.cpp=.o)
BIN_DIR = bin
TARGET  = $(BIN_DIR)/main.exe

.PHONY: all run clean rebuild

all: $(BIN_DIR) $(TARGET)
	@if not exist "$(BIN_DIR)\SDL2.dll"            copy "external\SDL2\x86_64-w64-mingw32\bin\SDL2.dll"             "$(BIN_DIR)" >nul
	@if not exist "$(BIN_DIR)\SDL2_image.dll"      copy "external\SDL2_image\x86_64-w64-mingw32\bin\SDL2_image.dll" "$(BIN_DIR)" >nul
	@if not exist "$(BIN_DIR)\SDL2_ttf.dll"        copy "external\SDL2_ttf\x86_64-w64-mingw32\bin\SDL2_ttf.dll"     "$(BIN_DIR)" >nul
	@if not exist "$(BIN_DIR)\SDL2_mixer.dll"      copy "external\SDL2_mixer\x86_64-w64-mingw32\bin\SDL2_mixer.dll" "$(BIN_DIR)" >nul
	@if not exist "$(BIN_DIR)\libgcc_s_seh-1.dll"  copy "$(MINGW_BIN)\libgcc_s_seh-1.dll"                          "$(BIN_DIR)" >nul
	@if not exist "$(BIN_DIR)\libstdc++-6.dll"     copy "$(MINGW_BIN)\libstdc++-6.dll"                             "$(BIN_DIR)" >nul
	@if not exist "$(BIN_DIR)\libwinpthread-1.dll"  copy "$(MINGW_BIN)\libwinpthread-1.dll"                         "$(BIN_DIR)" >nul

run: all
	$(BIN_DIR)\main.exe

$(BIN_DIR):
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-del /Q /S $(BIN_DIR) 2>nul
	-rmdir /Q /S $(BIN_DIR) 2>nul
	-del /Q $(subst /,\,$(OBJ)) 2>nul

rebuild: clean all
