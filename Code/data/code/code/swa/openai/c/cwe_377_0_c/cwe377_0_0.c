#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Erstellen Sie einen temporären Dateinamen
    char* filename = tmpnam(NULL);
    
    // Öffnen Sie die Datei zum Schreiben
    FILE* file = fopen(filename, "w");
    if (!file) {
        return NULL; // Fehler beim Öffnen der Datei
    }
    
    // Schreiben Sie die Ergebnisse in die Datei
    fprintf(file, "%s", results);
    
    // Schließen Sie die Datei
    fclose(file);
    
    // Geben Sie den Dateinamen zurück
    return filename;
}