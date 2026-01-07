#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Erzeuge einen temporären Dateinamen
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // Fehler beim Erstellen des temporären Dateinamens
    }

    // Öffne die Datei zum Schreiben
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Fehler beim Öffnen der Datei
    }

    // Schreibe die Ergebnisse in die Datei
    fprintf(file, "%s", results);
    
    // Schließe die Datei
    fclose(file);

    // Gebe den Dateinamen zurück
    return filename;
}