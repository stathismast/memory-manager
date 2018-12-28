#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 1000000

typedef struct Request{
    char rw;
    int page;
} Request;

int getFileSize(const char * file){
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    stream = fopen(file, "r");
    if (stream == NULL)
        exit(EXIT_FAILURE);


    int count = 0;
    while ((read = getline(&line, &len, stream)) != -1) {
        count++;
    }

    printf("Size %d\n", count);
    return count;
}

int main(void){
    Request * requests = malloc(LINES * sizeof(Request));

    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    stream = fopen("./traces/bzip.trace", "r");
    if (stream == NULL)
        exit(EXIT_FAILURE);


    int count = 0;
    while ((read = getline(&line, &len, stream)) != -1) {
        count++;

        char * addressString = strtok(line, " ");
        int address = strtol(addressString, NULL, 16);
        int page = address / 4048;
        char rw = strtok(NULL," \n")[0];

        printf("%s\t", line);
        printf("%c\t", rw);
        printf("%d\t", page);
        printf("%d\n", address);

        requests[count].rw = rw;
        requests[count].page = page;

        if(count == 100) break;
    }

    for(int i=0; i<100; i++){
        printf("%c %d\n", requests[i].rw, requests[i].page);
    }

    free(line);
    fclose(stream);

    getFileSize("./traces/bzip.trace");
    exit(EXIT_SUCCESS);
}
