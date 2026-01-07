#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Erstellen eines temporären Dateinamens
    char* filename = tempnam(NULL, "results_");
    if (filename == NULL) {
        return NULL; // Fehler beim Erstellen des Dateinamens
    }

    // Öffnen der temporären Datei zum Schreiben
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename); // Speicher freigeben, falls nicht erfolgreich
        return NULL; // Fehler beim Öffnen der Datei
    }

    // Schreiben der bereitgestellten Ergebnisse in die Datei
    fprintf(file, "%s", results);

    // Schließen der Datei
    fclose(file);

    // Rückgabe des Dateinamens
    return filename;
}