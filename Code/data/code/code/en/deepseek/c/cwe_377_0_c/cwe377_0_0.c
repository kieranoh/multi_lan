#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Check for NULL input
    if (results == NULL) {
        return NULL;
    }
    
    // Create a template for the temporary file
    char template[] = "/tmp/results_XXXXXX";
    
    // Create the temporary file
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Write the results to the file
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    // Check if write was successful
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template);  // Remove the temporary file
        return NULL;
    }
    
    // Close the file descriptor
    close(fd);
    
    // Allocate memory for the filename string
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);  // Remove the temporary file
        return NULL;
    }
    
    // Copy the template (which now contains the actual filename) to the allocated memory
    strcpy(filename, template);
    
    return filename;
}