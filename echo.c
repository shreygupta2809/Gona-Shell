#include "echo.h"

void echo_cmd()
{
    for (int i = 1; i < num_args; i++)
        printf("%s ", args[i]);
    printf("\n");
}
