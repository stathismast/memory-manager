#include <stdio.h>
#include "pageTable.h"
#include "parser.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: ./a.out k q\n");
        exit(0);
    }

    int k = atoi(argv[1]);
    int q = atoi(argv[2]);
    
    int max = 1000000;
    if(argc == 4){
        max = atoi(argv[3]);
    }

    if(q > max) q = max;

    Request * bzip = createRequestArray("./traces/bzip.trace");
    Request * gcc = createRequestArray("./traces/gcc.trace");

    PageTable * pt = newPageTable(10, k);

    int bzipCount = 0;
    int gccCount = 0;
    for(int i=0; i<2*max; i++){
        if((i/q)%2 == 0){
            addToPageTable(pt, bzip[bzipCount].page, bzip[bzipCount].rw);
            bzipCount++;
            printf("bzip %d %d\n", i, bzipCount);
        }
        else{
            addToPageTable(pt, gcc[gccCount].page, gcc[gccCount].rw);
            gccCount++;
            printf("gcc %d %d\n", i, gccCount);
        }
    }
    printPageTable(pt);

    deletePageTable(pt);

    free(bzip);
    free(gcc);
}
