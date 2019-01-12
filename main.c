#include <stdio.h>
#include <unistd.h>
#include "pageTable.h"
#include "psm.h"

int k;
int q;
int max;

void process(PSM * output, const char * file, int max){
    Request * trace = createRequestArray(file);

    for(int i=0; i<max; i++){
        semDown(output->semEmpty);
            memcpy(output->sharedMemory,&trace[i],sizeof(Request));
        semUp(output->semFull);
    }

    free(trace);
}

void manageArguments(int argc, char * argv[]){
    if(argc < 3){
        printf("Usage: ./a.out k q\n");
        exit(0);
    }

    k = atoi(argv[1]);
    q = atoi(argv[2]);
    
    max = 1000000;
    if(argc == 4){
        max = atoi(argv[3]);
    }

    if(q > max) q = max;
}

int main(int argc, char * argv[]){
    manageArguments(argc, argv);

    // Create the processes that will be reading the trace files. These 
    // processes will be sending each memory access request through a
    // PSM (Protected Shared Memory) structure.
    PSM * bzip = getPSM();
    PSM * gcc = getPSM();
    if(fork() == 0){
        process(bzip, "./traces/bzip.trace", max);
        free(bzip);
        free(gcc);
        exit(0);
    }
    if(fork() == 0){
        process(gcc, "./traces/gcc.trace", max);
        free(bzip);
        free(gcc);
        exit(0);
    }
    
    // Create the hashed page table structure
    PageTable * pt = newPageTable(10, k);

    // Receive every memory access request and add it to the page table
    Request req;
    for(int i=0; i<2*max; i++){
        if((i/q)%2 == 0){
            semDown(bzip->semFull);
                memcpy(&req,bzip->sharedMemory,sizeof(Request));
            semUp(bzip->semEmpty);
            addToPageTable(pt, req.page, req.rw, 0);
        }
        else{
            semDown(gcc->semFull);
                memcpy(&req,gcc->sharedMemory,sizeof(Request));
            semUp(gcc->semEmpty);
            addToPageTable(pt, req.page, req.rw, 1);
         }
    }

    // Print page table stats
    printStats(pt);

    // Detach shared memory and semaphores
    detachPSM(bzip);
    detachPSM(gcc);

    // Deallocate dynamically allocated memory
    deletePageTable(pt);
    free(bzip);
    free(gcc);
}
