#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Provjeri je li rezultat NULL
    if (results == NULL) {
        return NULL;
    }
    
    // Stvori šablon za privremenu datoteku
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    // Provjeri je li stvaranje datoteke uspjelo
    if (fd == -1) {
        return NULL;
    }
    
    // Zapiši rezultate u datoteku
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    // Ako pisanje nije uspjelo, zatvori datoteku i vrati NULL
    if (written != (ssize_t)len) {
        close(fd);
        return NULL;
    }
    
    // Zatvori datoteku
    close(fd);
    
    // Alociraj memoriju za naziv datoteke
    char* filename = (char*)malloc(strlen(template) + 1);
    if (filename == NULL) {
        return NULL;
    }
    
    // Kopiraj naziv datoteke u alociranu memoriju
    strcpy(filename, template);
    
    return filename;
}