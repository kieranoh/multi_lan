#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    char* filename = NULL;
    FILE* file = NULL;
    int fd;

    // Create a temporary file
    fd = mkstemp(filename);
    if (fd == -1) {
        return NULL; // Failed to create a temporary file
    }

    // Convert file descriptor to a file pointer
    file = fdopen(fd, "w");
    if (file == NULL) {
        close(fd);
        return NULL; // Failed to open the file pointer
    }

    // Write results to the temporary file
    fprintf(file, "%s", results);
    fclose(file); // Close the file to flush buffers and ensure data is written

    // Return the filename for further reading
    return filename;
}