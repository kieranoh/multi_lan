#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Temporäre Datei erstellen
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // Fehler beim Erstellen eines temporären Dateinamens
    }

    // Datei öffnen
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Fehler beim Öffnen der Datei
    }

    // Ergebnisse in die Datei schreiben
    if (fputs(results, file) == EOF) {
        fclose(file);
        return NULL; // Fehler beim Schreiben in die Datei
    }

    // Datei schließen
    fclose(file);

    // Dateiname zurückgeben
    return filename;
}