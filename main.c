#include <stdio.h>
#include "pageTable.h"
#include "parser.h"

int main(void){
    Request * bzip = createRequestArray("./traces/bzip.trace");
    Request * gcc = createRequestArray("./traces/gcc.trace");
    PageTable * pt = newPageTable(10);

    for(int i=0; i<50; i++){
        addToPageTable(pt, bzip[i].page, bzip[i].rw);
    }
    printPageTable(pt);

    deletePageTable(pt);

    free(bzip);
    free(gcc);
}
