#include "list.h"

typedef struct PageTable{
    List ** table;
    int size;
} PageTable;

PageTable * newPageTable(int size);
void printPageTable(PageTable * pt);
void addToPageTable(PageTable * pt, int page, char rw);
void deletePageTable(PageTable * pt);
