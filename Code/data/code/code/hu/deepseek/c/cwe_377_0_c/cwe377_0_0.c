#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }
    
    // Létrehozunk egy egyedi fájlnevet
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        return NULL;
    }
    
    // Írjuk a tartalmat a fájlba
    ssize_t bytes_written = write(fd, results, strlen(results));
    
    if (bytes_written == -1) {
        close(fd);
        return NULL;
    }
    
    // Zárjuk a fájlt
    close(fd);
    
    // Allokáljuk a memóriát a fájlnévnek
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        return NULL;
    }
    
    // Másoljuk a fájlnevet
    strcpy(filename, template);
    
    return filename;
}