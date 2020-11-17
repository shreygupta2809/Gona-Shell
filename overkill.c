#include "overkill.h"
#include "linked.h"

void overkill()
{
    while (head != NULL)
    {
        pid_t pid = head -> pid;
        if (kill(pid, SIGKILL) < 0){
            error = 1;
            perror("");
        }
        head = deleteNode(head, pid);
    }
}