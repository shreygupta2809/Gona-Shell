#include "redirect.h"

void redirect(char *new_cmd)
{
    if (strstr(new_cmd, "<"))
    {
        // inFile = dup(STDIN_FILENO);
        // inFile = 1;
        int in;
        for (int i = 0; i < num_args - 1; i++)
        {
            if (!strcmp(args[i], "<"))
            {
                in = open(args[i + 1], O_RDONLY);

                if (in < 0)
                {
                    error = 1;
                    perror("Error opening input file");
                    return;
                }
                else
                {
                    dup2(in, STDIN_FILENO);
                    close(in);
                }
                args[i] = "";
                args[i + 1] = "";
                // num_args -= 2;
                break;
            }
        }
    }
    if (strstr(new_cmd, ">"))
    {
        // outFile = 1;
        int out;
        for (int i = 0; i < num_args - 1; i++)
        {
            if (!strcmp(args[i], ">") || !strcmp(args[i], ">>"))
            {
                if (!strcmp(args[i], ">>"))
                {
                    out = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                else
                {
                    out = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }

                if (out < 0)
                {
                    error = 1;
                    perror("Error opening output file");
                }
                else
                {
                    dup2(out, STDOUT_FILENO);
                    close(out);
                }
                args[i] = "";
                args[i + 1] = "";
                // num_args -= 2;
                break;
            }
        }
    }
}