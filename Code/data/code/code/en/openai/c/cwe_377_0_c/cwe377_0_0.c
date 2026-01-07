#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tmpfile.h>

char* write_results(const char* results) {
    // Create a temporary file
    FILE* temp_file = tmpfile();
    if (temp_file == NULL) {
        return NULL; // Return NULL if temp file creation fails
    }

    // Write results to the temporary file
    if (fputs(results, temp_file) == EOF) {
        fclose(temp_file); // Close the file if writing fails
        return NULL; // Return NULL in case of writing error
    }

    // Get the name of the temporary file (not directly possible with tmpfile)
    // Instead, we can use a temporary file name pattern
    char* temp_filename = malloc(L_tmpnam);
    if (temp_filename == NULL) {
        fclose(temp_file); // Close the file if memory allocation fails
        return NULL; // Return NULL if memory allocation fails
    }

    // Generate a unique filename
    tmpnam(temp_filename);

    // Close the temporary file as we no longer need it in this context
    fclose(temp_file);
    
    // Return the dynamically allocated string containing the filename
    return temp_filename;
}