# OSproject1

===========================
Project Team member's names
===========================
1. Andrew Florial
2. Phalguna Rupanagudi
3. Eduardo Alvarez

========================
Contents of Tar Archive:
========================
1.functions.h         //declaration of functions and PCMD struct
2.exec_pipes.c        //function to implement pipes
3.exec_redirect.c     //function to implement io redirect
4.execute.c           //function to implement execution of commands
5.enVar.c             //interface to handle enviromental variables
6.call_wait.c         // 
7.main.c              //main driver program
8.parse.c             //functions to parse input and initialize PCMD
9.path_Res.c          //functions that implement path resolution for commands
10.prompt.c           //functions that handle prompt that tells user their working directory
11.README.md          //documentation
12.exec_builtIn.c     //handles built-in functinos such as io,etime,cd, etc.
13.makefile           //builds the project executable "shell"

=====================
Makefile instructions
=====================

To build: 
make

To clean: 
make clean

===========
Known bugs: 
===========


====================
Additional comments:
==================== 
An integral part of the system is the struct PCMD which is initialized during parsing
The struct contains the commands input by the user, and integers which indicate
special circumstances such as redirection, pipeing,background processing and others.
Similary, the structure of most files is a file for each section of the project with
the exception of the instances in which sections of the project overlapped and were 
included in the same file.

==================
Problem statement:
==================
Design and implement a basic shell interface that supports input/output redirection,
pipes, background processing, and a series of built in functions as specified below.
The shell should be robust (e.g. it should not crash under any circumstance beyond machine failure).
The required features should adhere to the operational semantics of the bash shell.

=============================
Steps taken to solve problem:
=============================
1.Setup shell input loop, makefile, github repository
2.Implemented pipes
3.Implemented parsing
4.Implemented enviromental variables
5.Implemented prompt
6.Implemented path resolution
7.Implemented background processes
8.Implemented built-ins
9.Edge-case testing
10. Documentation
11. Project Completion

============
Assumptions:
============
1. No more than three pipes will appear in a single line
2. You do not need to handle expansion of enviroment variables
3. input will be nore more than 255 characters
4. No handling of Zombie processes
5. Only built-ins in project specification supported
6. Built-in commands will not appear with I/O redirection

==================
Division of Labor:
==================
Andrew Florial
- Enviromental Variables
- Prompt
- Execution
- Pipes
- I/O Redirection
- Testing

Phalguna Rupanagudi
- Parsing
- Path Resolution
- Testing

Eduardo Alvarez
- I/O Redirection
- Documentation 
- Testing
