#include "headers/process.h"

// Function for the process that reads through the trace files and send
// the request through a shared memory segment protected by two semaphores
void process(PSM * output, const char * file, int max){
    Request * trace = createRequestArray(file);

    for(int i=0; i<max; i++){
        semDown(output->semEmpty);
            memcpy(output->sharedMemory,&trace[i],sizeof(Request));
        semUp(output->semFull);
    }

    free(trace);
}
