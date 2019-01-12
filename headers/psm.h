#include <stdlib.h>     // malloc
#include <wait.h>       // wait

#include "parser.h"
#include "semaphores.h"
#include "sharedMemory.h"

#ifndef PSM_H
#define PSM_H

// Stucture that contains sharedMemory that is protected using two semaphores
typedef struct PSM{
    Request * sharedMemory;
    int shmid;
    int semEmpty;
    int semFull;
} PSM;

#endif //PSM_H

int randomNumber(int lowerLimit, int upperLimit);
int randomID();
PSM * getPSM();
void detachPSM(PSM * psm);
