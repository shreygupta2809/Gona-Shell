#include "execute.h"

int tokenize(char str[])
{
    memset(args, 0, sizeof(args));
    int i = 0;
    char *token = strtok(str, " \t\n");
    if (token != NULL)
    {
        // strcpy(args[i++], token);
        args[i++] = token;
    }
    while (token != NULL)
    {
        token = strtok(NULL, " \t\n");
        if (token != NULL)
        {
            // strcpy(args[i++], token);
            args[i++] = token;
        }
    }
    return i;
}

void execute(char cmd[])
{
    error = 0;
    char new_cmd[1024];
    strcpy(new_cmd, cmd);
    num_args = tokenize(cmd);
    if (args[0] != NULL)
    {
        if (pipeHis)
            strcpy(his[h++ % 20], new_cmd);
        int back = 0;
        for (int i = 0; i < num_args; i++)
        {
            if (!strcmp(args[i], "&"))
            {
                back = 1;
                args[i] = "";
                break;
            }
        }
        // int in = 0, out = 0;
        if (strstr(new_cmd, "<") || strstr(new_cmd, ">"))
        {
            // inFile = outFile = 0;
            redirect(new_cmd);
            if (error)
                return;
            for (int i = 0; i < num_args; i++)
            {
                if (!strcmp(args[i], ">") || !strcmp(args[i], ">>") || !strcmp(args[i], "<"))
                {
                    fprintf(stderr, "Invalid Syntax\n");
                    error = 1;
                    return;
                }
            }
            // if (inFile)
            //     in = 2;
            // if (outFile)
            //     out = 2;
            // for (int i = 0; i < num_args; i++)
            //     printf("%s\n", args[i]);
            // printf("%d\n", strcmp(args[0], "cat"));
        }
        if (!strcmp(args[0], "quit"))
        {
            write_his();
            exit(0);
        }
        // else if (!strcmp(args[num_args - in - out - 1], "&"))
        // {
        //     // args[num_args - 1] = NULL;
        //     args[num_args - in - out - 1] = "";
        //     // num_args--;
        //     fg(1);
        // }
        else if (back)
        {
            fgbg(1);
        }
        else if (!strcmp(args[0], "cd"))
        {
            cd_cmd();
        }
        else if (!strcmp(args[0], "pwd"))
        {
            pwd_cmd();
        }
        else if (!strcmp(args[0], "echo"))
        {
            echo_cmd();
        }
        else if (!strcmp(args[0], "ls"))
        {
            ls_cmd();
        }
        else if (!strcmp(args[0], "pinfo"))
        {
            pinfo();
        }
        else if (!strcmp(args[0], "history"))
        {
            history();
        }
        else if (!strcmp(args[0], "setenv"))
        {
            setenv_cmd();
        }
        else if (!strcmp(args[0], "unsetenv"))
        {
            unsetenv_cmd();
        }
        else if (!strcmp(args[0], "kjob"))
        {
            kjob();
        }
        else if (!strcmp(args[0], "overkill"))
        {
            overkill();
        }
        else if (!strcmp(args[0], "bg"))
        {
            bg();
        }
        else if (!strcmp(args[0], "fg"))
        {
            fg();
        }
        else if (!strcmp(args[0], "jobs"))
        {
            jobs();
        }
        else
        {
            fgbg(0);
        }
        dup2(shellInFile, STDIN_FILENO);
        dup2(shellOutFile, STDOUT_FILENO);
        // if (strstr(new_cmd, "<") || strstr(new_cmd, ">"))
        // {
        //     if (inFile)
        //     {
        //         dup2(inFile, STDIN_FILENO);
        //         close(inFile);
        //     }
        //     if (outFile)
        //     {
        //         dup2(outFile, STDOUT_FILENO);
        //         close(outFile);
        //     }
        // }
    }
}