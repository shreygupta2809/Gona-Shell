#include "pinfo.h"

void pinfo()
{
    pid_t pid;
    if (num_args > 1)
        pid = atoi(args[1]);
    else
        pid = getpid();
    printf("pid -- %d\n", pid);

    char path2[1024];
    sprintf(path2, "/proc/%d/stat", pid);
    char *line1 = NULL;
    size_t len1 = 0, read1;

    FILE *fp1 = fopen(path2, "r");
    int flag = 0;
    if (fp1 == NULL){
        printf("Error opening %s file\n", path2);
        error = 1;
    }
    else
    {
        long long pgrp, tpgid;
        char str[1024];
        int i = 1;
        while (fscanf(fp1, "%s", str) == 1)
        {
            if (i == 5)
                pgrp = atoi(str);
            if (i == 8)
            {
                tpgid = atoi(str);
                break;
            }
            i++;
        }
        flag = (pgrp == tpgid);
        fclose(fp1);
    }

    char path[1024];
    sprintf(path, "/proc/%d/status", pid);
    char *line = NULL;
    size_t len = 0, read;

    FILE *fp = fopen(path, "r");
    if (fp == NULL){
        printf("Error opening %s file\n", path);
        error = 1;
    }
    else
    {
        int line_no = 0;
        while ((read = getline(&line, &len, fp)) != -1)
        {
            line_no++;
            if (line_no == 3)
            {
                char *token = strtok(line, " \t");
                token = strtok(NULL, " \t");
                printf("Process Status -- {%s", token);
                if (flag)
                    printf("+");
                printf("}\n");
            }
            if (line_no == 18)
            {
                char *token = strtok(line, " \t");
                token = strtok(NULL, " \t");
                printf("memory -- %s {​Virtual Memory​}\n", token);
                break;
            }
        }
        fclose(fp);
    }
    char path1[1024], buf[1024];
    sprintf(path1, "/proc/%d/exe", pid);
    size_t ret = readlink(path1, buf, 1024);
    if (ret > 0)
    {
        buf[ret] = 0;
        if (strstr(buf, home_dir))
        {
            char *short_path = strstr(buf, home_dir);
            short_path += strlen(home_dir);
            printf("Executable Path -- ~%s\n", short_path);
        }
        else
            printf("Executable Path -- %s\n", buf);
    }
    else{
        error = 1;
        printf("Error opening %s file\n", path1);
    }
}