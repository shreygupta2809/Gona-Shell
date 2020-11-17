#include "setenv.h"

void setenv_cmd()
{
    if (num_args != 2 && num_args != 3){
        error = 1;
        printf("Incorrect number of arguments\n");
    }
    else if (num_args == 2)
    {
        if (setenv(args[1], "", 1) < 0){
            error = 1;
            perror("");
        }
    }
    else if (setenv(args[1], args[2], 1) < 0){
        error = 1;
        perror("");
    }
}
