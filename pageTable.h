#include "list.h"

typedef struct PageTable{
    List ** table;
    int size;
    int k;
} PageTable;

PageTable * newPageTable(int size, int k);
void printPageTable(PageTable * pt);
void addToPageTable(PageTable * pt, int page, char rw);
void deletePageTable(PageTable * pt);
