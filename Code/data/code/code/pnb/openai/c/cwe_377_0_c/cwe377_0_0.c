#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Create a temporary file
    char* filename = tmpnam(NULL);
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Return NULL if file creation fails
    }

    // Write the provided results to the file
    fprintf(file, "%s", results);
    
    // Close the file
    fclose(file);
    
    // Return the name of the file
    return filename;
}