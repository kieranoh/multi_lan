#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }
    
    // Template für temporäre Datei
    char template[] = "/tmp/results_XXXXXX";
    
    // Temporäre Datei erstellen
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Ergebnisse in die Datei schreiben
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template);
        return NULL;
    }
    
    // Datei schließen
    if (close(fd) == -1) {
        unlink(template);
        return NULL;
    }
    
    // Dateinamen für Rückgabe duplizieren
    char* filename = strdup(template);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    return filename;
}