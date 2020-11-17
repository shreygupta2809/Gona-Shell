#include "unsetenv.h"

void unsetenv_cmd()
{
    if (num_args != 2)
    {
        error = 1;
        printf("Incorrect number of arguments\n");
    }
    else
    {
        if (getenv(args[1]))
        {
            if (unsetenv(args[1]) < 0)
            {
                error = 1;
                perror("");
            }
        }
        else
        {
            error = 1;
            fprintf(stderr, "Invaild env variable\n");
        }
    }
}