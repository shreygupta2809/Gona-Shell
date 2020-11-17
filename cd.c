#include "cd.h"

void cd_cmd()
{
    if (num_args > 2)
    {
        fprintf(stderr, "Too many arguments!\n");
        error = 1;
        return;
    }
    if (num_args == 1 || !strcmp(args[1], "~"))
    {
        char temp[1024];
        getcwd(temp, sizeof(temp));
        if (chdir(home_dir) < 0)
        {
            perror("Error changing directory");
            error = 1;
        }
        else
        {
            strcpy(olddir, temp);
        }
    }
    else if (strstr(args[1], "~"))
    {
        char temp[1024];
        getcwd(temp, sizeof(temp));
        char *name = args[1];
        name++;
        char *temp_dir = malloc(sizeof(home_dir));
        strcpy(temp_dir, home_dir);
        strcat(temp_dir, name);
        if (chdir(temp_dir) < 0)
        {
            perror("Error changing directory");
            error = 1;
        }
        else
        {
            strcpy(olddir, temp);
        }
    }
    else if (strstr(args[1], "-"))
    {
        if (strcmp(olddir, ""))
        {
            char temp[1024];
            getcwd(temp, sizeof(temp));
            printf("%s\n", olddir);
            if (chdir(olddir) < 0)
            {
                perror("Error changing directory");
                error = 1;
            }
            else
            {
                strcpy(olddir, temp);
            }
        }
        else
        {
            fprintf(stderr, "OLDPWD not set\n");
            error = 1;
        }
    }
    else
    {
        char temp[1024];
        getcwd(temp, sizeof(temp));
        if (chdir(args[1]) < 0)
        {
            perror("No such directory");
            error = 1;
        }
        else
        {
            strcpy(olddir, temp);
        }
    }
}