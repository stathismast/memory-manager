#include "headers/pageTable.h"

// Stats for both processes. Initialized to 0.
int reads[2] = {0};
int writes[2] = {0};
int pageFaults[2] = {0};
int flushes[2] = {0};
int writeBacks[2] = {0};

// Create a new page table
PageTable * newPageTable(int k){
    PageTable * pt = malloc(sizeof(PageTable));
    pt->size = k/2;
    pt->k = k;

    pt->table = malloc(pt->size * sizeof(List*));
    for(int i=0; i<pt->size; i++){
        pt->table[i] = newList();
    }

    return pt;
}

// Print all relevant stats for both processes
void printStats(PageTable * pt){
    printf("Process\t\tReads\t\tWrites\t\tPage Faults\tFlushes\t\tWrite Backs\n");
    printf("bzip\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", reads[0], writes[0], pageFaults[0], flushes[0], writeBacks[0]);
    printf("gcc\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", reads[1], writes[1], pageFaults[1], flushes[1], writeBacks[1]);
}

// Go through all the lists containing pages and
// flush the ones that belong to the given process 
void flushPageTable(PageTable * pt, int pid){
    for(int i=0; i<pt->size; i++){
        pt->table[i] = flushList(pt->table[i], pid);
    }
    flushes[pid]++;
}

// Add a page to the page table. If the page doesn't exist then we have
// a page fault. Once we reach 'k' page faults the page tables is flushed
// of all the pages that belong to the given process.
void addToPageTable(PageTable * pt, int page, char rw, int pid){
    int index = (unsigned int) page % pt->size;

    // If the page that is requested is not present in the page table
    if(!isInList(pt->table[index], page)){
        
        // If we've reached the limit of 'k' page faults flush the
        // page table of all the pages that belong to this process
        if(pageFaults[pid] % pt->k == 0 && pageFaults[pid] != 0)
            flushPageTable(pt, pid);

        // Add the new page to the page table and
        // increase the total number of page faults
        addToList(pt->table[index], page, rw, pid);
        pageFaults[pid]++;
    }

    // If this page request is a write request
    // change the dirty bit of that page to 1.
    if(rw == 'W'){
        changeDirtyBit(pt->table[index], page);
        writes[pid]++;
    }
    else reads[pid]++;
}

// Delete the given page table
void deletePageTable(PageTable * pt){
    for(int i=0; i<pt->size; i++){
        deleteList(pt->table[i]);
    }
    free(pt->table);
    free(pt);
}
