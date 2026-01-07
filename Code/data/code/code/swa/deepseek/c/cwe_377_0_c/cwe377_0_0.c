#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Validate input
    if (results == NULL) {
        return NULL;
    }
    
    // Create a temporary file name template
    char template[] = "/tmp/results_XXXXXX";
    
    // Create a temporary file using mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Write results to the file
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template);
        return NULL;
    }
    
    // Close the file descriptor
    close(fd);
    
    // Allocate memory for the filename to return
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    // Copy the filename
    strcpy(filename, template);
    
    return filename;
}