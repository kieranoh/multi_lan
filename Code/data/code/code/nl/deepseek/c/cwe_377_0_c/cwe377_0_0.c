#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Controleer of de invoer geldig is
    if (results == NULL) {
        return NULL;
    }
    
    // Maak een sjabloon voor het tijdelijke bestand
    char template[] = "/tmp/results_XXXXXX";
    
    // Maak een uniek tijdelijk bestand met mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Schrijf de resultaten naar het bestand
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    // Controleer of het schrijven succesvol was
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template);  // Verwijder het tijdelijke bestand
        return NULL;
    }
    
    // Sluit het bestand
    close(fd);
    
    // Wijs geheugen toe voor de bestandsnaam
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);  // Verwijder het tijdelijke bestand
        return NULL;
    }
    
    // Kopieer de bestandsnaam
    strcpy(filename, template);
    
    return filename;
}