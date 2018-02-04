shell: main.c functions.h exec_pipes.c enVar.c exec_redirect.c execute.c prompt.c genTestPCMD.c
	gcc -o shell main.c exec_pipes.c enVar.c exec_redirect.c execute.c prompt.c	genTestPCMD.c
