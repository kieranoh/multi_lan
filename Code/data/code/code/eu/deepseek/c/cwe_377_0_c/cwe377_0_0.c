#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Egiaztatu sarrera balioduna den
    if (results == NULL) {
        return NULL;
    }
    
    // Sortu fitxategi temporalerako izen patroia
    char template[] = "/tmp/results_XXXXXX";
    
    // Sortu fitxategi temporala
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Idatzi emaitzak fitxategian
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    // Itxi fitxategi deskriptorea
    close(fd);
    
    // Egiaztatu idazketa arrakastatsua izan den
    if (written != (ssize_t)len) {
        // Ezabatu fitxategia idazketa errore bat gertatu bada
        unlink(template);
        return NULL;
    }
    
    // Kopiatu fitxategi izena string dinamiko batera
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}