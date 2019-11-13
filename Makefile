CC=gcc

all:
	$(CC) -o bin\gl.exe src\main.c src\glad.c -Iinclude -Llib -lglfw3 -lgdi32 -lopengl32