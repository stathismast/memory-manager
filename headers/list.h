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
Node * copyNode(Node * original);
void addToList(List * list, int part, char rw, int pid);
void addNodeToList(List * list, Node * node);
List * flushList(List * list, int pid);
int isInList(List * list, int page);
void changeDirtyBit(List * list, int page);
void deleteNodes(Node * node);
void deleteList(List * list);
void clearList(List * list);
