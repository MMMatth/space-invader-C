CFLAGS = -O3 -Dmain=SDL_main
LDFLAGS = -lm -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image
SDL2_INCLUDE_DIR = C:\dev\SDL2\x86_64-w64-mingw32\include 
SDL2_LIBRARIES_DIR = C:\dev\SDL2\x86_64-w64-mingw32\lib

INC = include/sdl2-light.h include/const.h include/world.h include/display.h include/sprite.h include/sdl2-ttf-light.h include/meteors.h include/projectile.h include/struct.h include/sound.h include/animate.h
SRC = src/main.c src/sdl2-light.c src/world.c src/display.c src/sprite.c src/sdl2-ttf-light.c src/meteors.c src/projectile.c src/sound.c src/animate.c
OBJ = $(SRC:src/%.c=lib/%.o)

PROG = bin/start.exe

all: $(PROG)

$(PROG): $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@ -L $(SDL2_LIBRARIES_DIR)


lib/%.o: src/%.c $(INC)
	gcc $(CFLAGS) -c $< -o $@ -I $(SDL2_INCLUDE_DIR)

doc : 
	cd doc && doxygen Doxyfile

test:
	gcc -IC:\dev\SDL2\x86_64-w64-mingw32\include src/tests.c lib/world.o lib/sprite.o lib/wall.o  -o bin/tests.exe -lSDL2

map:
	gcc src/map_generator.c -o bin/map_generator.exe
	./bin/map_generator.exe

clean:
	del /q lib\*.o bin\start.exe bin\tests.exe bin\map_generator.exe
	del /q doc\html\* doc\latex\*
