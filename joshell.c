#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>
#include "I_go_to_the_gym.h"
#define JOSHEL INT_MAX
int main() {
    char *buf;
    while (JOSHEL) {
        buf = read_in();
        char * input[300002];
        int i=0;
        char * arg;
        while ((arg = strsep(&buf, " ")) != NULL) {
            if (*arg != '\0') input[i++] = arg;
        }
        if (!strcmp(input[0], "exit"))
            break; 
        child_exec(input);
        free(buf);
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
        execvp(*args, args);
    }
    return f;
}
