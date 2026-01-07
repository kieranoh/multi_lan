#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char* write_results(const char* results) {
    // Prüfe auf ungültige Eingabe
    if (results == NULL) {
        return NULL;
    }
    
    // Erstelle ein temporäres Dateimuster
    char template[] = "/tmp/results_XXXXXX";
    
    // Erstelle eine temporäre Datei mit mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        // Fehler beim Erstellen der temporären Datei
        return NULL;
    }
    
    // Schreibe die Ergebnisse in die Datei
    size_t len = strlen(results);
    ssize_t bytes_written = write(fd, results, len);
    
    if (bytes_written != (ssize_t)len) {
        // Fehler beim Schreiben
        close(fd);
        unlink(template);  // Lösche die temporäre Datei
        return NULL;
    }
    
    // Schließe die Datei
    close(fd);
    
    // Allokiere Speicher für den Dateinamen
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        // Speicherallokation fehlgeschlagen
        unlink(template);  // Lösche die temporäre Datei
        return NULL;
    }
    
    // Kopiere den Dateinamen
    strcpy(filename, template);
    
    return filename;
}