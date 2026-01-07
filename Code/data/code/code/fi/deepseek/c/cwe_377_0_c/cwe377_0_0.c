#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Tarkista, että results ei ole NULL
    if (results == NULL) {
        return NULL;
    }
    
    // Luo väliaikainen tiedostonimi
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        // Epäonnistui väliaikaisen tiedoston luominen
        return NULL;
    }
    
    // Kirjoita tulokset tiedostoon
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        // Kirjoitus epäonnistui
        close(fd);
        unlink(template); // Poista tiedosto
        return NULL;
    }
    
    // Sulje tiedosto
    close(fd);
    
    // Allokoi muisti palautettavalle tiedostonimelle
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template); // Poista tiedosto
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}