#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Temporäre Datei erstellen
    char* filename = tempnam(NULL, "results_");
    if (filename == NULL) {
        perror("Fehler beim Erstellen des Dateinamens");
        return NULL;
    }

    // Datei öffnen zum Schreiben
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei");
        free(filename);
        return NULL;
    }

    // Ergebnisse in die Datei schreiben
    fprintf(file, "%s", results);

    // Datei schließen
    fclose(file);

    // Dateinamen zurückgeben
    return filename;
}