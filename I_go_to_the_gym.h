int child_exec(char **);
char * read_in();
char ** split_cmd(char *);
char ** get_args(char * cmd);
char * get_wd(char *, size_t);
int custom_exec(char **);
char *** cut_in_half(char **, int);
char * concat(char **);
