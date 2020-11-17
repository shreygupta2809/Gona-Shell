#include "history.h"

int get_his()
{
    char filename[1024];
    strcpy(filename, home_dir);
    strcat(filename, "/");
    strcat(filename, "shell_history.txt");
    FILE *fp;
    fp = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0, read;

    h = 0;
    if (fp)
    {
        while ((read = getline(&line, &len, fp)) != -1)
        {
            line[read - 1] = '\0';
            strcpy(his[h++], line);
        }
        fclose(fp);
    }
    return h;
}

void write_his()
{
    char filename[1024];
    strcpy(filename, home_dir);
    strcat(filename, "/");
    strcat(filename, "shell_history.txt");
    // strcpy(filename, "shell_history.txt");
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Unable to write history in file %s\n", filename);
        perror("Error in opening file");
        error = 1;
    }
    else
    {
        int num = h >= 20 ? 20 : h;
        for (int j = h > 20 ? h % 20 : 0; num > 0; j = (j + 1) % 20)
        {
            fprintf(fp, "%s\n", his[j]);
            num--;
        }
        fclose(fp);
    }
}

void history()
{
    int i, num;
    if (num_args > 2)
    {
        fprintf(stderr, "Too many arguments\n");
        error = 1;
        return;
    }
    else if (num_args == 2)
    {
        i = atoi(args[1]);
        if (i > h)
        {
            if (h > 20)
                i = 20;
            else
                i = h;
        }
        if (i > 20)
            i = 20;
    }
    else
        i = h > 10 ? 10 : h;
    num = i;
    for (int j = (20 + h % 20 - i) % 20; num > 0; j = (j + 1) % 20)
    {
        printf("%s\n", his[j]);
        num--;
    }
}