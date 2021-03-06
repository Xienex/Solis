CC = ccache g++
CFLAGS = -m64 -c -Wall -Wextra -I/mingw64/include -Iinclude  -std=c++1z  -g
	
ifeq ($(OS),Windows_NT)
	LDFLAGS = -L/mingw64/lib -lopengl32 -lglew32 -lglfw3 -lassimp -lvulkan-1 
else
	LDFLAGS = -lGL -lGLEW -lglfw -lassimp -lSOIL
endif
SOURCES := $(wildcard  src/*.cpp src/game/*.cpp src/core/*.cpp src/graphics/*.cpp src/physics/*.cpp src/physics/shape/*.cpp src/graphics/gui/*.cpp src/graphics/opengl/*.cpp src/graphics/vulkan/*.cpp)
EXECUTABLE = hello

ALL_OBJECTS := $(SOURCES:.cpp=.o)


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(ALL_OBJECTS)
	$(CC) $(ALL_OBJECTS)  $(LDFLAGS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm src/*.o src/*/*.o src/*/*/*.o *.exe