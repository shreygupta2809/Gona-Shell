#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <signal.h>

char *commands[32];
// char args[32][1024];
char *args[64];
char home_dir[1024];
char hostname[1024];
char *username;
char cwd[1024];
char olddir[1024];
int num_args;
char his[20][1024];
int h;
// int inFile, outFile;
pid_t shellpid;
int error;
int pipeHis;
int noprint;

struct Node
{
    pid_t pid;
    char name[1024];
    int job;
    struct Node *next;
};
int shellInFile, shellOutFile;
struct Node *head;

#endif