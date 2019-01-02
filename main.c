#include "parser.h"

int main(void){
    Request * bzip = createRequestArray("./traces/bzip.trace");
    Request * gcc = createRequestArray("./traces/gcc.trace");

    free(bzip);
    free(gcc);
}
