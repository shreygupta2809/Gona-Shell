# GSH (GONA SHELL)

## main.c

This file is the main file for the execution of the shell. It initialises the _home_dir_, _hostname_, _username_. Here the history is loaded and the main while loop runs and waits for user input. The commands are also separated by the **_;_** if there are multiple commands in a single line and calls execution for each one of them.

```c
int main()
```

## cd.c

This file contains the implementation of the **_cd_** command used to change directories in linux.

```c
void cd_cmd()
```

## echo.c

This file contains the implementation of the **_echo_** command used to print text on the shell.

```c
void echo_cmd()
```

## pwd.c

This file contains the implementation of the **_pwd_** command used to get the current working directory.

```c
void pwd_cmd()
```

## ls2.c

This file contains the implementation of the **_ls_** command used to get the contents of a directory. Two of its flags _-a_ and _-l_ have also been implemented. It can also show the contents of various directories given as its arguments.

```c
void ls_cmd()
void read_from_dir()
void print_full()
```

## pinfo.c

This file contains the implementation of the user defined **_pinfo_** command which can be used to get the process information of the current process by default or a process specified by its pid which is given as argument.

```c
void pinfo()
```

## fgbg.c

This file contains the implementation for the execution of foreground and background processes. Background processes can be run by placing an **&** at the end of the command.

```c
void fgbg(int back)
```

The variable **_back_** is set to 1 if the process is a background process or 0 if it is a foreground process.

## linked.c

This file contains the implementation of a linked list to store the background processes. Each node contains:

1. The pid of the process
1. Full name of the process
1. The pointer to the next process in the list.

```c
struct Node *insertNode(struct Node *head, pid_t pid, char *name, int jnum);
struct Node *deleteNode(struct Node *head, pid_t pid);
char *findNode(struct Node *head, pid_t pid);
pid_t findNodebyJobNumber(struct Node *head, int job);
```

## signal_handler.c

This file contains the implementation of the signal handler to receive the **SIGCHILD** signal from the child background processes. After receiving the signal it determines whether the child process terminated normally and prints it to _stderr_ along with its name, pid and status. It also includes the signal handlers for dealing with **SIGINT** and **SIGTSTP** signal related to _Control C_ and _Control Z_.

```c
void signal_handler(int signal);
void signal_control_c(int signal);
void signal_control_z(int signal);
```

## prompt.c

This file contains the implementation of the **_prompt_** which is to be printed before any command the user enters. It showcases the username, hostname, and the current working directory.

```c
void prompt()
```

## history.c

This file contains the implementation of the **_history_** command used to display the users most recent commands. It shows the 10 most recent commands by default but the number of commands to be shown can be given as an argument. In this I store upto 20 of the users commands. On exitting the shell the commands are stored in a file _shell_history.txt_ and are loaded from this again on start of the shell. While running the commands are stored in an array to reduce overhead of reading and writing from a file.

```c
int get_his();
void write_his();
void history();
```

## execute.c

This file handles the excution of all the commands. It initially tokenises the command on the basis of spaces, tabs, and newlines. Then the command is checked with the given inbuilt commands and handled accordingly with the help of the helper functions for each command.

```c
int tokenize(char str[]);
void execute(char cmd[]);
```

## bg.c

This file conatains the command **_bg_** command which is used to change status of a background process from running to stopped.

```c
void bg();
```

## fg.c

This file conatains the command **_fg_** command which is used to change bring a background process into the foreground and it change its status from stopped to running if required.

```c
void fg();
```

## jobs.c

This file conatains the command **_jobs_** command which displays all the current background processes.

```c
void jobs();
```

## kjob.c

This file conatains the command **_kjob_** command which can be used to send a signal to a background process by its job number.

```c
void kjob();
```

## overkill.c

This file conatains the command **_overkill_** command which is used to kill (send SIGKILL) all the background processes at once.

```c
void overkill();
```

## pipes.c

This file is used to implement the pipe functionality in the commands. I basically parse the pipes by the **|** symbol and then execute each subsequent command. For example in a | b | c, initially I tokenise the commands by | symbol. Then each of the commands is run sequentially such that output of one command becomes the input of the following command if any. I have not implemented piping by forking i.e., I don't form separate child processes for each pipe command (a, b, c).

```c
int tokenize_pipe(char str[], char *pipeCommands[32]);
void pipe_cmd(char cmd[]);
```

## redirect.c

This file is used to implement the redirect functionality in the commands.

```c
void redirect(char * new_cmd);
```

## setenv.c

This file is used to implement the **_setenv_** command which can be used to set new environment variables or change the values of pre-existing env variables.

```c
void setenv_cmd();
```

## unsetenv.c

This file is used to implement the **_unsetenv_** command which can be used to unset pre-existing environment variables.

```c
void unsetenv_cmd();
```

## headers.h

This file contains all the libraries needed for the execution of the shell. It also contains all the global variables used throughout the running of the shell.

> Each file mentioned above excluding main.c also has a header file ( .h file ) for that command which contains the function declarations of the functions of the corresponding .c file.

## Makefile

This file contains the code to run the shell. To compile the shell, run:

```bash
$ make
```

After compilation, to start the shell run:

```bash
$ ./gsh
```

---

## GENERAL ASSUMPTIONS

1. The maximum length of the _hostname_ is 1024 characters long.
1. The maximum length of the _home_dir_ and the _cwd_ (current working directory) is 1024 characters long.
1. The maximum number of _commands_ in a single line is 32.
1. The maximum number of _args_ (arguments) in a single command is 32 and the maximum length of the argument can be 1024 characters.
1. The maximum number of pipe commands i.e., a | b | c ... where a, b, c are pipe commands can be 32
