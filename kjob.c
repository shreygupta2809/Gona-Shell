#include "kjob.h"
#include "linked.h"

void kjob()
{
    if (num_args != 3)
    {
        fprintf(stderr, "Incorrect number of Arguments\n");
        error = 1;
    }
    else
    {
        int job_no, signal;
        job_no = atoi(args[1]);
        signal = atoi(args[2]);
        pid_t pid = findNodebyJobNumber(head, job_no);
        if (pid)
        {
            if (kill(pid, signal) < 0)
            {
                error = 1;
                perror("");
            }
        }
        else
        {
            fprintf(stderr, "Please enter valid job number\n");
            error = 1;
        }
    }
}