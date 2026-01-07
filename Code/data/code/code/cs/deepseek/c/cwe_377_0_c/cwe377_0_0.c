#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Vytvoření dočasného souboru
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        return NULL;
    }
    
    // Zápis dat do souboru
    if (results != NULL) {
        size_t len = strlen(results);
        ssize_t written = write(fd, results, len);
        
        if (written != (ssize_t)len) {
            close(fd);
            unlink(template);
            return NULL;
        }
    }
    
    // Uzavření souboru
    close(fd);
    
    // Alokace paměti pro návratovou hodnotu
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}