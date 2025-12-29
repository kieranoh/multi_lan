#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Generáljunk egy ideiglenes fájlnevet
    char* filename = malloc(256);
    if (filename == NULL) {
        return NULL; // Memóriafoglalási hiba
    }
    
    snprintf(filename, 256, "/tmp/results_XXXXXX");
    
    // Létrehozzuk az ideiglenes fájlt
    int fd = mkstemp(filename);
    if (fd == -1) {
        free(filename);
        return NULL; // Fájl létrehozási hiba
    }
    
    // Írjuk bele a megadott eredményeket
    if (results != NULL) {
        write(fd, results, strlen(results));
    }
    
    // Zárjuk be a fájlt
    close(fd);
    
    // Visszatérünk a fájl nevével
    return filename;
}