#include "linked.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <dirent.h>
// #include <time.h>
// #include <pwd.h>
// #include <grp.h>
// #include <sys/wait.h>
// #include <signal.h>

// struct Node
// {
//     pid_t pid;
//     char name[1024];
//     int job;
//     struct Node *next;
// };

// struct Node *head;

struct Node *insertNode(struct Node *head, pid_t pid, char name[], int jnum)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last = head;

    new_node->pid = pid;
    strcpy(new_node->name, name);
    new_node->job = jnum;
    new_node->next = NULL;

    if (!head)
    {
        head = new_node;
        return head;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    return head;
}

struct Node *deleteNode(struct Node *head, pid_t pid)
{
    struct Node *temp = head;
    struct Node *last = head;

    if (temp && temp->pid == pid)
    {
        last = temp->next;
        free(temp);
        return last;
    }

    while (temp && temp->pid != pid)
    {
        last = temp;
        temp = temp->next;
    }

    last->next = temp->next;
    free(temp);
    return head;
}

char *findNode(struct Node *head, pid_t pid)
{
    if (!head)
        return NULL;

    struct Node *temp = head;

    while (temp && temp->pid != pid)
        temp = temp->next;

    if (!temp)
        return NULL;

    return temp->name;
}

pid_t findNodebyJobNumber(struct Node *head, int job)
{
    if (!head)
        return 0;

    struct Node *temp = head;

    while (temp && temp->job != job)
        temp = temp->next;

    if (!temp)
        return 0;

    return temp->pid;
}

// int main()
// {
//     head = insertNode(head, 3, "hello");
//     head = deleteNode(head, 3);
//     head = insertNode(head, 4, "ello");
//     head = insertNode(head, 5, "llo");
//     pid_t t = findNodebyJobNumber(head, 1);
//     printf("%d\n", t);
//     t = findNodebyJobNumber(head, 2);
//     printf("%d\n", t);
//     head = insertNode(head, 3, "hello");
//     t = findNodebyJobNumber(head, 3);
//     printf("%d\n", t);
//     head = deleteNode(head, 5);
//     t = findNodebyJobNumber(head, 1);
//     printf("%d\n", t);
//     t = findNodebyJobNumber(head, 2);
//     printf("%d\n", t);
//     t = findNodebyJobNumber(head, 3);
//     printf("%d\n", t);
//     if (findNode(head, 7))
//     {
//         head = deleteNode(head, 7);
//     }
//     if (findNode(head, 6))
//     {
//         head = deleteNode(head, 6);
//     }
// }