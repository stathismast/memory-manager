#include "list.h"

typedef struct PageTable{
    List ** table;
    int size;
    int k;
} PageTable;

PageTable * newPageTable(int size, int k);
void printPageTable(PageTable * pt);
void flushPageTable(PageTable * pt, int pid);
void addToPageTable(PageTable * pt, int page, char rw, int pid);
void deletePageTable(PageTable * pt);
