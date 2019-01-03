#include <stdio.h>
#include "pageTable.h"
#include "parser.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: ./a.out k\n");
        exit(0);
    }

    int k = atoi(argv[1]);

    Request * bzip = createRequestArray("./traces/bzip.trace");
    // Request * gcc = createRequestArray("./traces/gcc.trace");

    PageTable * pt = newPageTable(10, k);

    for(int i=0; i<1000000; i++){
        addToPageTable(pt, bzip[i].page, bzip[i].rw);
    }
    printPageTable(pt);

    deletePageTable(pt);

    free(bzip);
//     free(gcc);
}
