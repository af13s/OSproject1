shell: main.c functions.h exec_pipe.c multipipe.c parse.c
	gcc -o shell main.c exec_pipe.c multipipe.c parse.c