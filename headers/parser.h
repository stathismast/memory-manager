#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Request{
    char rw;
    int page;
} Request;

Request * createRequestArray(const char * file, int max);
void manageArguments(int argc, char * argv[]);
