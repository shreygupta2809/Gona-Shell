#include "pipes.h"
#include "execute.h"

int tokenize_pipe(char str[], char *pipeCommands[32])
{
    int i = 0;
    char *token = strtok(str, "|");
    if (token != NULL)
        pipeCommands[i++] = token;
    while (token != NULL)
    {
        token = strtok(NULL, "|");
        if (token != NULL)
            pipeCommands[i++] = token;
    }
    return i;
}

void pipe_cmd(char cmd[])
{
    strcpy(his[h++ % 20], cmd);
    pipeHis = 0;
    int numpipes = 0;
    for (int i = 0; i < strlen(cmd); i++)
    {
        if (cmd[i] == '|')
            numpipes++;
    }
    char *pipeCommands[32];
    int pipe_commands = tokenize_pipe(cmd, pipeCommands);
    // for (int i = 0; i < pipe_commands; i++)
    // {
    //     printf("%s\n", pipeCommands[i]);
    // }
    if (pipe_commands != numpipes + 1)
    {
        error = 1;
        fprintf(stderr, "Invalid Syntax\n");
        return;
    }
    int fds[pipe_commands - 1][2];

    // printf("%d\n", pipe_commands);
    for (int i = 0; i < pipe_commands - 1; i++)
    {
        if (pipe(fds[i]) < 0)
        {
            error = 1;
            perror("");
        }
        if (!i)
        {
            int outFile = dup(STDOUT_FILENO);
            dup2(fds[i][1], STDOUT_FILENO);
            close(fds[i][1]);
            execute(pipeCommands[i]);
            dup2(outFile, STDOUT_FILENO);
            close(outFile);
        }
        else
        {
            int inFile = dup(STDIN_FILENO);
            int outFile = dup(STDOUT_FILENO);
            dup2(fds[i][1], STDOUT_FILENO);
            dup2(fds[i - 1][0], STDIN_FILENO);
            close(fds[i][1]);
            close(fds[i - 1][0]);
            execute(pipeCommands[i]);
            dup2(inFile, STDIN_FILENO);
            dup2(outFile, STDOUT_FILENO);
            close(inFile);
            close(outFile);
        }
    }
    int inFile = dup(STDIN_FILENO);
    dup2(fds[pipe_commands - 2][0], STDIN_FILENO);
    close(fds[pipe_commands - 2][0]);
    execute(pipeCommands[pipe_commands - 1]);
    dup2(inFile, STDIN_FILENO);
    close(inFile);
}
