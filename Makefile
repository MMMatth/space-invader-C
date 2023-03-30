CFLAGS = -O3 -Dmain=SDL_main
LDFLAGS = -lm -lmingw32 -lSDL2main -lSDL2
SDL2_INCLUDE_DIR = C:\dev\SDL2\x86_64-w64-mingw32\include
SDL2_LIBRARIES_DIR = C:\dev\SDL2\x86_64-w64-mingw32\lib

INC = include/sdl2-light.h include/const.h include/world.h include/display.h include/sprite.h
SRC = src/main.c src/sdl2-light.c src/world.c src/display.c src/sprite.c
OBJ = $(SRC:src/%.c=lib/%.o)

PROG = bin/start.exe

all: $(PROG)

$(PROG): $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@ -L $(SDL2_LIBRARIES_DIR)


lib/%.o: src/%.c $(INC)
	gcc $(CFLAGS) -c $< -o $@ -I $(SDL2_INCLUDE_DIR)

doc: 
	doxygen doc/Doxyfile

test:
	gcc src/tests.c lib/world.o -o bin/tests


clean:
	del /q lib\*.o bin\start.exe bin\tests.exe
	del /q doc\html\* doc\latex\*
