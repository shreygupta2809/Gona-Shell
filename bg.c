#include "bg.h"
#include "linked.h"

void bg()
{
    if (num_args != 2)
    {
        fprintf(stderr, "Incorrect number of arguments");
        error = 1;
    }
    else
    {
        int jnum = atoi(args[1]);
        pid_t pid = findNodebyJobNumber(head, jnum);
        if (pid <= 0)
        {
            fprintf(stderr, "Invalid job number\n");
            error = 1;
            return;
        }
        if (kill(pid, SIGCONT) < 0)
        {
            error = 1;
            perror("");
        }
    }
}