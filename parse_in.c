#include <stdio.h>
#include <stdlib.h>
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

char ** split_cmd(char * line) {
    char ** cmds = calloc(64, sizeof(char));
    
    return NULL;
}
