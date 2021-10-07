all: compile run

compile:
	g++ -I ../include/ -L ../lib/ -o main ../main.cpp ../glad.c -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32
run:
	.\main.exe