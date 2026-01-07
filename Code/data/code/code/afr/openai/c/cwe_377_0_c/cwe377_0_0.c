#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Temp file creation
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // Error handling for temp filename generation
    }

    // Open the temporary file for writing
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Error handling for file opening
    }

    // Write results to the file
    if (fputs(results, file) == EOF) {
        fclose(file);
        return NULL; // Error handling for writing to the file
    }

    // Close the file
    fclose(file);
    
    // Return the filename for further reading
    return filename;
}