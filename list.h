#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    struct Node * first;
    struct Node * last;
    int length;
} List;

typedef struct Node{
    int page;
    int dirty;
    int pid;
    struct Node * next;
} Node;

List * newList();
Node * newNode(int part, char rw, int pid);
void addToList(List * list, int part, char rw, int pid);
void emptyList(List * list);
List * flushList(List * list, int pid);
int isInList(List * list, int page);
void changeDirtyBit(List * list, int page);
void deleteNodes(Node * node);
void printList(List * list);
char notEmpty(List * list);
