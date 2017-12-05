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

//char *** cut_in_half(char ** args, int i);

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
            free(args);
        }
        free(cmds);
        free(buf);
    }
    printf("\n");
    return JOSHEL;
}
int custom_exec(char ** args) {
    size_t i = -1;
    while (args[++i] != NULL) {
        if (!strcmp(args[i],">")) {
            args[i] = NULL;
            int new_file = open(args[i+1],O_WRONLY | O_TRUNC | O_CREAT, 0644); //OPEN THE FILE AND REMEMBER TO ADD THE CLOSE BETWEEN THE LAST 2 DUP2s
            int tmp_file;
            tmp_file = dup(STDOUT_FILENO);
            dup2(new_file, STDOUT_FILENO);
            int f = custom_exec(args);
            close(new_file);
            dup2(tmp_file, STDOUT_FILENO);
            return f;

        }
        if (!strcmp(args[i],">>")) {
            args[i] = NULL;
            int new_file = open(args[i+1],O_WRONLY | O_APPEND | O_CREAT, 0644);
            int tmp_file;
            tmp_file=dup(STDOUT_FILENO);
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
            tmp_file = dup(STDIN_FILENO);
            dup2(new_file, STDIN_FILENO);
            int f = custom_exec(args);
            close(new_file);
            dup2(tmp_file, STDIN_FILENO);
            return f;

        } /*
        if (!strcmp(args[i],"|")) {
            args[i] = NULL;
            char ** parsed1 = cut_in_half(args, i)[0];
            char ** parsed2 = cut_in_half(args, i)[1];
	    FILE *fp = popen(, "r");
	    if (!fp) {
	      printf("ya dun goofed \n");
	      return;
	    }
	    int a = dup(STDIN_FILENO);
	    int old = dup2(fileno(fp), STDIN_FILENO);
	    int f = custom_execs(parsed2);
	    dup2(a, old);
	    pclose(fp);
	    return f;
	    } */

    }
    return child_exec(args);
}
/*
char *** cut_in_half(char ** args, int i) {
    char ** a[2];
    int x;
    for (x = 0; x < i; x++) {
        a[0][x] = args[x];
    }
    x++; //LMFAO i'm writing it this way just to trigger you gilvir
    while (args[x] != NULL) {
        a[1][x-i] = args[x];
        x++;
    }
    return a;
}
*/
//returns child pid
int child_exec( char ** args) {
    int f = fork();
    if (f) {
        int wstatus;
        waitpid(f, &wstatus, 00);
    }
    else {
        int f = execvp(*args, args);
        if (f == -1) {
            fprintf(stderr, "joshell: %s : %s\n",*args, strerror(errno));
        }
    }
    return f;
}
