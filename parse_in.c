#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
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
  int x;
  char *file_name;
  int addq;
  int gtq = 0;
  int ltq = 0;
  //while you can still split the cmds:
  while ((cmd = strtok_r(line, ";,\n", &line)) != NULL) {
    addq = 1;
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
      /*
      if (gtq) {
	file_name = cmd;
	int new_file = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	dup2(new_file, 0);
	close(new_file);
	gtq = 0;
      }
      if (ltq) {
	file_name = cmd;
	int new_file2 = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	dup2(new_file2, 1);
	close(new_file2);
	ltq = 0;
      }
      if (!strcmp(cmd, ">")) {
	addq = 0;
	gtq = 1;
      }
      if (!strcmp(cmd, "<")) {
        addq = 0;
	ltq = 1;
      }
      if (addq) {     */
	cmds[i++] = cmd;
	/*      }
      else {
	i++;
	}*/
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
  size_t args_sz = 64;
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


