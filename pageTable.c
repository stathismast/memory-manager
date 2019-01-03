#include "pageTable.h"

int reads = 0;
int writes = 0;
int pageFaults = 0;

PageTable * newPageTable(int size, int k){
    PageTable * pt = malloc(sizeof(PageTable));
    pt->size = size;
    pt->k = k;

    pt->table = malloc(size * sizeof(List*));
    for(int i=0; i<size; i++){
        pt->table[i] = newList();
    }

    return pt;
}

void printPageTable(PageTable * pt){
    for(int i=0; i<pt->size; i++){
        printf("\n%d\n",i);
        printList(pt->table[i]);
    }

    printf("\nReads: %d\nWrites: %d\nPage Faults: %d\n", reads, writes, pageFaults);
}

void flushPageTable(PageTable * pt){
    for(int i=0; i<pt->size; i++){
        emptyList(pt->table[i]);
    }
}

void addToPageTable(PageTable * pt, int page, char rw){
    int index = (unsigned int) page % pt->size;

    if(isInList(pt->table[index], page)){
        // printf("%d is already in index %d\n", page, index);
    }
    else{
        // printf("%d is not in index %d. Page fault.\n", page, index);

        if(pageFaults % pt->k == 0){
            printf("Reached %d page faults. Flushing...\n", pageFaults);
            flushPageTable(pt);
            // printPageTable(pt);
        }

        addToList(pt->table[index], page, rw);
        pageFaults++;
    }

    if(rw == 'W'){
        changeDirtyBit(pt->table[index], page);
        writes++;
    }
    else reads++;
}

void deletePageTable(PageTable * pt){
    for(int i=0; i<pt->size; i++){
        emptyList(pt->table[i]);
        free(pt->table[i]);
    }
    free(pt->table);
    free(pt);
}
