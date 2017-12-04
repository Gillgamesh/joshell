#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include "I_go_to_the_gym.h"
#include <errno.h>
#define JOSHEL INT_MAX
#define EXIT "exit"
#define CD "cd"
#define READ 0
#define WRITE 1
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
            } else
            custom_exec(args);
        //    free(args);
        }
        wait(NULL);
        //free(cmds);
        //free(buf);
    }
    printf("\n");
    return JOSHEL;
}
int custom_exec(char ** args) {
    size_t i = -1;
    while (args[++i]) {
        if (!strcmp(args[i],">")) {
            args[i] = NULL;
            int new_file = open(args[i+1],O_WRONLY | O_TRUNC | O_CREAT, 0644); //OPEN THE FILE AND REMEMBER TO ADD THE CLOSE BETWEEN THE LAST 2 DUP2s
            int tmp_file;
            dup2(STDOUT_FILENO, tmp_file);
            dup2(new_file, STDOUT_FILENO);
            int f = child_exec(args);
            close(new_file);
            dup2(tmp_file, STDOUT_FILENO);
            return f;

        }
        if (!strcmp(args[i],">>")) {
            args[i] = NULL;
            int new_file = open(args[i+1],O_WRONLY | O_APPEND | O_CREAT, 0644);
            int tmp_file;
            dup2(STDOUT_FILENO, tmp_file);
            dup2(new_file, STDOUT_FILENO);
            int f = custom_exec(args);
            close(new_file);
            dup2(tmp_file, STDOUT_FILENO);
            return f;

        }
        if (!strcmp(args[i],"<")) {
            args[i] = NULL;
            int new_file = open(args[i+1],O_RDONLY); //OPEN THE FILE AND REMEMBER TO ADD THE CLOSE BETWEEN THE LAST 2 DUP2s
            if (new_file == -1) {
                fprintf(stderr, "joshell: %s: %s\n",args[i+1], strerror(errno));
                return -1;
            }
            int tmp_file;
            dup2(STDIN_FILENO, tmp_file);
            dup2(new_file, STDIN_FILENO);
            int f = child_exec(args);
            close(new_file);
            dup2(tmp_file, STDIN_FILENO);
            return f;

        }
        if (!strcmp(args[i],"|")) {
            args[i] = NULL;
            int fds[2];
            pipe(fds);
            int tmp_in;
            int tmp_out;
            dup2(STDIN_FILENO, tmp_in);
            dup2(STDOUT_FILENO, tmp_out);
            dup2(fds[READ], STDIN_FILENO);
            dup2(fds[WRITE], STDIN_FILENO);
            int f = child_exec(args);
            int g = child_exec(args+i+1);
            dup2(tmp_in, STDIN_FILENO);
            dup2(tmp_out, STDOUT_FILENO);
            return f;

        }
                
    }
    return child_exec(args);
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
