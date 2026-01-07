#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Überprüfen, ob die Eingabe gültig ist
    if (results == NULL) {
        return NULL;
    }
    
    // Template für temporäre Datei erstellen
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        // Fehler beim Erstellen der temporären Datei
        return NULL;
    }
    
    // Ergebnisse in die Datei schreiben
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        // Fehler beim Schreiben
        close(fd);
        unlink(template); // Datei löschen
        return NULL;
    }
    
    // Datei schließen
    close(fd);
    
    // Dateinamen für Rückgabe duplizieren
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template); // Datei löschen
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}