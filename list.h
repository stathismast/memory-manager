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
    struct Node * next;
} Node;

List * newList();
Node * newNode(int part, char rw);
void addToList(List * list, int part, char rw);
void emptyList(List * list);
int isInList(List * list, int page);
void changeDirtyBit(List * list, int page);
void deleteNodes(Node * node);
void printList(List * list);
char notEmpty(List * list);
