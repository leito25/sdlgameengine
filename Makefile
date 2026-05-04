CXX = g++
CXXFLAGS = -std=c++17 -Isrc -Ilibs -Ilibs/glm -Ilibs/imgui -Ilibs/lua -Ilibs/python -Ilua-5.4.6/src \
           -Ipython-3.10.11 -Ipybind11-2.11.1/include \
           -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2 \
           -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 \
           -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2 \
           -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2

LDFLAGS = -LSDL2-2.30.5/x86_64-w64-mingw32/lib \
          -LSDL2_image-2.8.2/x86_64-w64-mingw32/lib \
          -LSDL2_ttf-2.22.0/x86_64-w64-mingw32/lib \
          -LSDL2_mixer-2.8.0/x86_64-w64-mingw32/lib \
          -Llua-5.4.6/src \
          -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua

SRC = src/Main.cpp \
      libs/imgui/imgui.cpp \
      libs/imgui/imgui_draw.cpp \
      libs/imgui/imgui_widgets.cpp \
      libs/imgui/imgui_demo.cpp \
      libs/imgui/imgui_sdl.cpp

OBJ = $(SRC:.cpp=.o)

BIN_DIR = bin
TARGET = $(BIN_DIR)/main.exe
PYTHON_GAME = $(BIN_DIR)/PythonGame.exe

all: $(BIN_DIR) $(TARGET)

# Python Game source files
PYTHON_GAME_SRC = examples/PythonGame.cpp \
                  libs/imgui/imgui.cpp \
                  libs/imgui/imgui_draw.cpp \
                  libs/imgui/imgui_widgets.cpp \
                  libs/imgui/imgui_demo.cpp \
                  libs/imgui/imgui_sdl.cpp

PYTHON_GAME_OBJ = $(PYTHON_GAME_SRC:.cpp=.o)

PythonGame: $(BIN_DIR) $(PYTHON_GAME)

$(PYTHON_GAME): $(PYTHON_GAME_OBJ)
	$(CXX) $(PYTHON_GAME_OBJ) -o $(PYTHON_GAME) $(LDFLAGS)

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJ) $(PYTHON_GAME_OBJ) $(TARGET) $(PYTHON_GAME) 2>nul || exit 0
	rmdir /Q /S $(BIN_DIR) 2>nul || exit 0
