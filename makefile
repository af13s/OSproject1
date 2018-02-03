shell: main.c functions.h exec_pipes.c parse.c
	gcc -o shell main.c exec_pipes.c parse.c
