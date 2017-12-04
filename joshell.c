#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>
#include "I_go_to_the_gym.h"
#define JOSHEL INT_MAX
int main() {
    char buffer[256];
    char *buf = buffer;
    while (JOSHEL) {
        //fgets(buf, sizeof(buffer), stdin);
        char * input[32];
        int i=0;
        buf = "ls -l";
        while (input[i++] = strsep(&buf, " "));
        if (!strcmp(input[0], "exit"))
            break; 
        child_exec(input);
    }
    printf("\n");
    return JOSHEL;
}


//returns child pid
int child_exec( char ** args) {
    int f = fork();
    if (f) {
    } 
    else {
        execvp((char *) args, args);
    }
    return f;
}
