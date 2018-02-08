shell: main.c functions.h exec_Pipes.c enVar.c exec_Redirect.c execute.c prompt.c parse.c exec_BuiltIn.c call_Wait.c path_Res.c
	gcc -o shell main.c exec_Pipes.c enVar.c exec_Redirect.c execute.c prompt.c parse.c exec_BuiltIn.c call_Wait.c path_Res.c
