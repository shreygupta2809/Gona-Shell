#include "fg.h"
#include "linked.h"

void fg()
{
    char name[1024];
    int job = atoi(args[1]);
    // pid_t shellpid = getpid();
    int status;
    pid_t pid = findNodebyJobNumber(head, job);
    if (pid <= 0)
    {
        fprintf(stderr, "Invalid job number");
        error = 1;
        return;
    }
    strcpy(name, findNode(head, pid));
    printf("%d\n", pid);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    tcsetpgrp(0, getpgid(pid));
    if (kill(pid, SIGCONT) < 0)
    {
        error = 1;
        perror("Error");
    }
    // waitpid(pid, NULL, 0);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpgid(shellpid));
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    head = deleteNode(head, pid);
    if (WIFSTOPPED(status))
    {
        error = 1;
        struct Node *temp = head;
        int jnum = 1;
        while (temp != NULL)
        {
            jnum = temp->job + 1;
            temp = temp->next;
        }
        head = insertNode(head, pid, name, jnum);
        printf("%s with PID %d suspended\n", name, pid);
    }
}