# CC=g++
CC=clang++

CFLAGS=-lGL -lX11 -lglfw -lXi -ldl -Wall -I ./include/ -I /usr/include/ -I ./vendor/

main: 
	$(CC) $(CFLAGS) -o render.out main.cpp ./src/*.cpp ./vendor/glad/glad.c
	./render.out

debug:
	$(CC) $(CFLAGS) -g -o render.out main.cpp .src/*.cpp ./vendor/glad/glad.c
	gdb ./render.out

build:
	$(CC) $(CFLAGS) -v -o render.out main.cpp .src/*.cpp ./vendor/glad/glad.c

clean:
	rm ./render.out
