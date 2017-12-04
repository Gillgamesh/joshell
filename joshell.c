#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>
#include "I_go_to_the_gym.h"
#include <errno.h>
#define JOSHEL INT_MAX
#define EXIT "exit"
#define CD "cd"
int main() {
    char *buf;
    while (JOSHEL) {
        char user[256], host[256], wd[256];
        struct passwd * pw = getpwuid(getuid());
        strcpy(user, pw->pw_name);
        gethostname(host, sizeof(host));
        char * cwd = getcwd(wd, sizeof(wd));
        printf("[%s@%s:%s]$ ", user, host, wd);

        buf = read_in();
        char ** cmds = split_cmd(buf);
        int i=-1;
        while (cmds[++i] != NULL) {
            char ** args = get_args(cmds[i]);
            if (!strcmp(args[0],EXIT)) return 1;
            if (!strcmp(args[0], CD)) {
                if (args[1]) {
                    chdir(args[1]);
                }
                else {

                }
            }
            child_exec(args);
            free(args);
        }
        free(cmds);
        free(buf);
    }
    printf("\n");
    return JOSHEL;
}


//returns child pid
int child_exec( char ** args) {
    int f = fork();
    if (f) {
        wait(NULL);
    } 
    else {
        int f = execvp(*args, args);
        if (f == -1) {
            fprintf(stderr, "joshell: %s : %s\n",*args, strerror(errno));
        }
    }
    return f;
}
