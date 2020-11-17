#include "signal_handler.h"
#include "linked.h"
#include "prompt.h"

void signal_handler(int signal)
{
    // printf("1\n");
    int status;
    char *name;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid > 0)
    {
        if (name = findNode(head, pid))
        {
            if (!status)
                fprintf(stderr, "\n%s with pid %d exited normally\n", name, pid);
            else
                fprintf(stderr, "\n%s with pid %d exited abnormally\n", name, pid);
            head = deleteNode(head, pid);
            prompt();
            fflush(stdout);
        }
    }
}

void signal_control_c(int sig)
{
    // printf("2\n");
    error = 1;
    printf("\n");
    prompt();
    fflush(stdout);
}

void signal_control_z(int sig)
{
    // printf("3\n");
    printf("\n");
    prompt();
    fflush(stdout);
}