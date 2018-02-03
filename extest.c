#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{

    char x[3][50] = {"/bin/ls"};
    char ** y = (char **) x;
    printf("%s\n",&y[0]);
    y[2] = NULL;
    
    

if ( fork() == 0 )
        execv( y[0], y ); // child: call execv with the path and the args
   
                // parent: wait for the child (not really necessary)

    return 0;
}
