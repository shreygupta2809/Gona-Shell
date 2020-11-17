#include "prompt.h"

void prompt()
{
    if (getcwd(cwd, sizeof(cwd)))
    {
        if (error != -1)
        {
            if (error)
                printf(":'(");
            else
                printf(":')");
        }
        if (strstr(cwd, home_dir))
        {
            char *short_path = strstr(cwd, home_dir);
            short_path += strlen(home_dir);
            printf("<%s@%s: ~%s>", username, hostname, short_path);
        }
        else
            printf("<%s@%s: %s>", username, hostname, cwd);
    }
    else
    {
        error = 1;
        perror("Error getting current directory");
    }
}
