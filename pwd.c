#include "pwd.h"

void pwd_cmd()
{
    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
    }
    else
    {
        error = 1;
        perror("Error getting current working directory");
    }
}