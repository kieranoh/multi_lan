#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Kontrollera att results inte är NULL
    if (results == NULL) {
        return NULL;
    }
    
    // Skapa ett unikt temporärt filnamn
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        // Misslyckades att skapa temporär fil
        return NULL;
    }
    
    // Skriv resultaten till filen
    size_t len = strlen(results);
    ssize_t bytes_written = write(fd, results, len);
    
    if (bytes_written != (ssize_t)len) {
        // Misslyckades att skriva all data
        close(fd);
        unlink(template); // Ta bort filen
        return NULL;
    }
    
    // Stäng filen
    close(fd);
    
    // Allokera minne för filnamnet
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template); // Ta bort filen om minnesallokering misslyckas
        return NULL;
    }
    
    // Kopiera filnamnet
    strcpy(filename, template);
    
    return filename;
}