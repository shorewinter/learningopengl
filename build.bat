@echo off
g++ -o bin\gl.exe src\main.cpp src\glad.c -Iinclude -Llib -lglfw3 -lgdi32 -lopengl32
if %errorlevel% neq 0 exit /b %errorlevel%
bin\gl.exe