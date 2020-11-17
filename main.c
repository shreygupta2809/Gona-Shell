#include "prompt.h"
#include "signal_handler.h"
#include "execute.h"
#include "pipes.h"

int main()
{
    gethostname(hostname, 32);
    username = getenv("USER");

    getcwd(cwd, sizeof(cwd));
    strcpy(olddir, "");
    // getcwd(olddir, sizeof(olddir));
    strcpy(home_dir, cwd);
    h = get_his();
    signal(SIGCHLD, signal_handler);
    signal(SIGINT, signal_control_c);
    signal(SIGTSTP, signal_control_z);
    shellInFile = dup(STDIN_FILENO);
    shellOutFile = dup(STDOUT_FILENO);
    shellpid = getpid();
    error = -1;

    while (1)
    {
        prompt();
        fflush(stdout);

        // char cad[1024], c;
        size_t bufSize = 0;
        int read;
        char *cad = 0;

        // scanf("%[^\n]s", cad);
        // scanf("%c", &c);
        read = getline(&cad, &bufSize, stdin);
        if (read < 0)
        {
            printf("\n");
            exit(0);
        }

        cad[read - 1] = '\0';
        // if (read == 0)
        //     continue;
        if (cad[0] == '\0')
            continue;
        int i = 0;
        char *token = strtok(cad, ";");
        if (token != NULL)
        {
            commands[i++] = token;
        }
        while (token != NULL)
        {
            token = strtok(NULL, ";");
            if (token != NULL)
            {
                commands[i++] = token;
            }
        }

        for (int j = 0; j < i; j++)
        {
            // printf("%s--\n", commands[j]);
            if (commands[j] != NULL)
            {
                pipeHis = 1;
                if (strstr(commands[j], "|"))
                    pipe_cmd(commands[j]);
                else
                    execute(commands[j]);
            }
        }
    }
    free(commands);
    return 0;
}