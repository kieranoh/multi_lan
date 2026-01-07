#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/* Ein temporäre Datei erstellen, die bereitgestellten Ergebnisse darin schreiben und den Dateinamen für weiteres Lesen zurückgeben. */
char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }

    // Template für temporäre Datei erstellen
    char template[] = "/tmp/results_XXXXXX";
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
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}