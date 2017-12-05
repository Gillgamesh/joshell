# joshell
By Aryan Bhatt and Gilvir Gill
it is BIG

Features:
* Functioning shell that can execute commands of unlimited length using forking
* Can execute multiple commands in a line using ; separation (the number of commands is limited by your machine's RAM
* Implements basic redirection using >, <, and >>
* Can read in commands from an external file (using redirection)

Attempted:
* Multiple redirection
* Pipes

Bugs:
* Joshel is limited by INT_MAX (not BIG enough)

Functions:
```c
int child_exec(char **);
char * read_in();
char ** split_cmd(char *);
char ** get_args(char *);
int custom_exec(char **);
```

```c
int child_exec(char **);
```
Takes in a String array of arguments
Forks, and the child runs the command using execvp
Returns the child's pid

```c
char * read_in();
```
Reads from whatever file is defined to be STDIN
Uses realloc to create a sufficiently large buffer to hold the string
If realloc fails due to lack of available memory space, it returns null
Otherwise, it returns the string that was read in (null terminated)

```c
char ** split_cmd(char *);
```
Takes in a null terminated raw input line
Returns a String array that points to each individual command (separates using '\n' and ';' as delimiters

```c
char ** get_args(char *);
```
Takes in a null terminated string
Returns an array of pointers to the arguments, in order
The returned pointer will NOT be the same as the inputed pointer

```c
int custom_exec(char **);
```
Wrapper function for child_exec
Accounts for < and >
Tries to account for |, but doesn't really work
