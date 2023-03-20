
main:ei1.c sdl2-light.c sdl2-light.h
	gcc ei1.c sdl2-light.c `sdl2-config --cflags --libs` -o ei1

corr:ei1-corr.c sdl2-light.c sdl2-light.h
	gcc ei1-corr.c sdl2-light.c `sdl2-config --cflags --libs` -o ei1-corr

clean:
	rm ei1 ei1-corr


