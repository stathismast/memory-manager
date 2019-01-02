#include "parser.h"

Request * createRequestArray(const char * file){

    // Alocate space for each memory access. For each memeory access
    // we store the page it needs and whether its a read or write.
    Request * requests = malloc(1000000 * sizeof(Request));

    // Open and begin reading the file
    FILE * stream = fopen(file, "r");
    char * line = NULL;
    size_t len = 0;

    int count = 0;
    while (getline(&line, &len, stream) != -1) {
        
        // Parse each line to retreive the page each request
        // needs and whether its a read or write
        int address = strtol(strtok(line, " "), NULL, 16);
        int page = address / 4048;
        char rw = strtok(NULL," \n")[0];

        // Store the read/write bit and the page number in the allocated array
        requests[count].rw = rw;
        requests[count].page = page;
        count++;
    }
    free(line);
    fclose(stream);

    return requests;
}
