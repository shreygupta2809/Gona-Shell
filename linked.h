#include "headers.h"

#ifndef __LINKED_H
#define __LINKED_H

struct Node *insertNode(struct Node *head, pid_t pid, char *name, int jnum);
struct Node *deleteNode(struct Node *head, pid_t pid);
char *findNode(struct Node *head, pid_t pid);
pid_t findNodebyJobNumber(struct Node *head, int job);

#endif // __LINKED_H