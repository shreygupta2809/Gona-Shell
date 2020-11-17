#include "fgbg.h"

void fgbg(int back)
{

    int j = 0;
    for (int i = 0; i < num_args; i++)
    {
        if (strcmp(args[i], ""))
        {
            args[j++] = args[i];
        }
    }
    args[j] = 0;

    // for (int i = 0; i < j; i++)
    // {
    //     printf("%s\n", args[i]);
    // }
    pid_t pid;
    int status;
    pid = fork();
    if (pid < 0)
    {
        perror("Failed forking");
        error = 1;
    }
    else if (!pid)
    {
        setpgid(0, 0);
        if (execvp(args[0], args) < 0)
        {
            fprintf(stderr, "Error executing %s command\n", args[0]);
            perror("");
            exit(1);
        }
    }
    else
    {
        dup2(shellOutFile, STDOUT_FILENO);
        dup2(shellInFile, STDIN_FILENO);
        if (back)
        {
            char name[1024];
            strcpy(name, args[0]);
            for (int i = 1; i < j; i++)
            {
                strcat(name, " ");
                strcat(name, args[i]);
            }

            struct Node *temp = head;
            int jnum = 1;
            while (temp != NULL)
            {
                jnum = temp->job + 1;
                temp = temp->next;
            }
            head = insertNode(head, pid, name, jnum);
            printf("%d\n", pid);
        }
        else
        {
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
            // setpgid(pid, 0);
            // tcsetpgrp(0, getpgid(pid));
            // waitpid(pid, &status, WUNTRACED);
            // tcsetpgrp(0, getpgid(shellpid));
            tcsetpgrp(0, pid);
            waitpid(pid, &status, WUNTRACED);
            tcsetpgrp(0, shellpid);
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);
            if (WIFSTOPPED(status))
            {
                error = 1;
                char name[1024];
                strcpy(name, args[0]);
                for (int i = 1; i < j; i++)
                {
                    strcat(name, " ");
                    strcat(name, args[i]);
                }

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

            // waitpid(pid, &status, 0);
        }
    }
}
