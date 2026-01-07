#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // Error generating a temporary file name
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Error opening the file
    }

    fprintf(file, "%s", results);
    fclose(file);

    return filename; // Return the name of the temporary file
}