#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * reads from whatever stdin is defined to be
*/
char * read_in() {
    size_t i = 0;
    size_t buff_sz = 1024;
    char * buff = calloc(buff_sz, sizeof(char));
    int c;
    while ((buff != NULL) && ((c = getchar()) != '\n') && ( c != EOF)) {
        //if you've reached the end of your buffer but not the end of your file, double your buffer size
        //this statement is true iff i is currently at the last possible index
        if ( i+1 >= buff_sz) {
            buff_sz *= 2;
            void * tmp = realloc(buff, buff_sz * sizeof(char));
            if (tmp != NULL) {
                buff = (char *) tmp;
            }
            else {
                free(buff);
                return NULL;
            }
        }
        buff[i++] = c;
    }
    buff[i] = 0; //null terminate ur string
    return buff;
}
/*
 * takes in raw input line, null terminated
 * returns pointer array to each individual command
*/
char ** split_cmd(char * line) {
    size_t cmds_sz = 64;
    char ** cmds = calloc(cmds_sz, sizeof(char));
    char * cmd;
    size_t i = 0;
    //while you can still split the cmds:
    while ((cmd = strtok_r(line, ";,\n", &line)) != NULL) {
        //if the cmd isn't null, add it to cmds:
        if (*cmd != '\0') {
            if ( i+1 >= cmds_sz) {
                cmds_sz *= 2;
                void * tmp = realloc(cmds, cmds_sz * sizeof(char));
                if (tmp != NULL) {
                    cmds = (char **) tmp;
                }
                else {
                    free(cmds);
                    return NULL;
                }
            }
            cmds[i++] = cmd;
        }
    }
    cmds[i] = NULL;
    
    return cmds;
}
/*
 * takes in a null terminated string
 * returns an array of pointers to the arguments, in order. the returned pointer will NOT be the same as the pointer to the cmd.
*/
char ** get_args(char * cmd) {
    size_t args_sz = 32;
    char ** args = calloc(args_sz, sizeof(char));
    int i = 0;
    char * arg;
    while ((arg = strsep(&cmd, " ")) != NULL) {
        //if the arg isnt \0, add it to the args list.
        if (*arg != '\0') {
            if ( i+1 >= args_sz) {
                args_sz *= 2;
                void * tmp = realloc(args, args_sz * sizeof(char));
                if (tmp != NULL) {
                    args = (char **) tmp;
                }
                else {
                    free(args);
                    return NULL;
                }
            }
            args[i++] = arg;
        }
    }
    args[i] = 0;
    return args;
    
}


