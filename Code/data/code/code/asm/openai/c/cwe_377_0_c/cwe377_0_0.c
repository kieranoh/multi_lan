#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Temporäre Datei erstellen
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // Fehler bei der Dateinamenerstellung
    }

    // Datei zum Schreiben öffnen
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Fehler beim Öffnen der Datei
    }

    // Ergebnisse in die Datei schreiben
    fprintf(file, "%s", results);

    // Datei schließen
    fclose(file);

    // Dateinamen zurückgeben
    return filename;
}