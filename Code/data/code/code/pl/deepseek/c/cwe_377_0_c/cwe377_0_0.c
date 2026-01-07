#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Sprawdź poprawność wejścia
    if (results == NULL) {
        return NULL;
    }
    
    // Utwórz szablon nazwy pliku tymczasowego
    char template[] = "/tmp/results_XXXXXX";
    
    // Utwórz tymczasowy plik
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Zapisz dane do pliku
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template);
        return NULL;
    }
    
    // Zamknij plik
    close(fd);
    
    // Alokuj pamięć dla nazwy pliku
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    // Skopiuj nazwę pliku
    strcpy(filename, template);
    
    return filename;
}