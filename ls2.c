#include "ls.h"

void print_full(char filepath[], char *file)
{
    // char filepath[2048];
    // strcpy(filepath, path);
    // strcat(filepath, "/");
    // strcat(filepath, file);

    struct stat f = {0};
    if (stat(filepath, &f) == 0)
    {
        mode_t perm = f.st_mode;
        char permissions[11];
        permissions[0] = S_ISDIR(perm) ? 'd' : '-';
        permissions[1] = ((perm & S_IRUSR) ? 'r' : '-');
        permissions[2] = ((perm & S_IWUSR) ? 'w' : '-');
        permissions[3] = ((perm & S_IXUSR) ? 'x' : '-');
        permissions[4] = ((perm & S_IRGRP) ? 'r' : '-');
        permissions[5] = ((perm & S_IWGRP) ? 'w' : '-');
        permissions[6] = ((perm & S_IXGRP) ? 'x' : '-');
        permissions[7] = ((perm & S_IROTH) ? 'r' : '-');
        permissions[8] = ((perm & S_IWOTH) ? 'w' : '-');
        permissions[9] = ((perm & S_IXOTH) ? 'x' : '-');
        permissions[10] = '\0';
        // printf("%s\n", permissions);
        char mtime[80];
        time_t t = f.st_mtime;
        struct tm lt;
        localtime_r(&t, &lt);
        strftime(mtime, sizeof mtime, "%b %d %Y %H:%M", &lt);
        struct passwd *pw = getpwuid(f.st_uid);
        struct group *gr = getgrgid(f.st_gid);
        printf("%s  %ld\t%s\t%s\t%ld\t%s  %s\n", permissions, f.st_nlink, pw->pw_name, gr->gr_name, f.st_size, mtime, file);
    }
    else
    {
        error = 1;
        perror("Error reading file permission!");
    }
}

void read_from_dir(char path[], int full, int hide)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        printf("%s:\n", path);
        if (full)
        {
            long long total = 0;
            while ((dir = readdir(d)) != NULL)
            {
                char filepath[2048];
                strcpy(filepath, path);
                strcat(filepath, "/");
                strcat(filepath, dir->d_name);

                struct stat direc = {0};
                if (stat(filepath, &direc) == 0)
                    total += direc.st_blocks;
            }
            printf("total %lld\n", total / 2);
            rewinddir(d);
        }
        while ((dir = readdir(d)) != NULL)
        {
            char filepath[2048];
            strcpy(filepath, path);
            strcat(filepath, "/");
            strcat(filepath, dir->d_name);

            if (full && hide)
                print_full(filepath, dir->d_name);
            else if (full && !hide)
            {
                if (dir->d_name[0] != '.')
                    print_full(filepath, dir->d_name);
            }
            else if (!full && hide)
                printf("%s\n", dir->d_name);
            else if (!full && !hide)
            {
                if (dir->d_name[0] != '.')
                    printf("%s\n", dir->d_name);
            }
        }
        printf("\n");
    }
    else
    {
        struct stat f = {0};
        if (stat(path, &f) == 0)
        {
            if (full)
                print_full(path, path);
            else
                printf("%s\n", path);
            printf("\n");
        }
        else
        {
            error = 1;
            perror("Error opening directory or file!");
        }
    }
}

void ls_cmd()
{
    int full = 0, hide = 0, dir_present = 0;
    for (int i = 1; i < num_args; i++)
    {
        if (!strcmp(args[i], "-l"))
            full = 1;
        else if (!strcmp(args[i], "-a"))
            hide = 1;
        else if (!strcmp(args[i], "-al") || !strcmp(args[i], "-la"))
        {
            full = 1;
            hide = 1;
        }
        else if (strcmp(args[i], ""))
            dir_present = 1;
    }
    if (!dir_present)
    {
        char path[] = ".";
        read_from_dir(path, full, hide);
    }
    else
    {
        for (int i = 1; i < num_args; i++)
        {
            if (!strcmp(args[i], "-l") || !strcmp(args[i], "-a") || !strcmp(args[i], "-al") || !strcmp(args[i], "-la"))
                continue;
            else
            {
                char path[1024];
                // printf("%s:\n", args[i]);
                if (strstr(args[i], "~"))
                {
                    char *name = args[i];
                    name++;
                    strcpy(path, home_dir);
                    strcat(path, name);
                }
                else
                    strcpy(path, args[i]);

                read_from_dir(path, full, hide);
            }
        }
    }
}