shell: main.c functions.h exec_pipes.c parse.c enVar.c exec_redirect.c
	gcc -o shell main.c exec_pipes.c parse.c enVar.c exec_redirect.c
