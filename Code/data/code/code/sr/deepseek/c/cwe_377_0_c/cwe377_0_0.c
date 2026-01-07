#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Provjera ulaznih parametara
    if (results == NULL) {
        return NULL;
    }
    
    // Kreiranje šablona za privremenu datoteku
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        // Neuspješno kreiranje privremene datoteke
        return NULL;
    }
    
    // Pisanje rezultata u datoteku
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        // Neuspješno pisanje u datoteku
        close(fd);
        unlink(template); // Ukloni datoteku
        return NULL;
    }
    
    // Zatvaranje datoteke
    close(fd);
    
    // Dinamička alokacija stringa za ime datoteke
    char* filename = (char*)malloc(strlen(template) + 1);
    if (filename == NULL) {
        // Neuspješna alokacija memorije
        unlink(template); // Ukloni datoteku
        return NULL;
    }
    
    // Kopiranje imena datoteke u dinamički alocirani string
    strcpy(filename, template);
    
    return filename;
}