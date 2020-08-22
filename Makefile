CC=g++

all:
	$(CC) -o bin\gl.exe src\main.cpp src\glad.c -Iinclude -Llib -lglfw3 -lgdi32 -lopengl32