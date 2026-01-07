#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    char* filename = tempnam(NULL, "results_");
    if (filename == NULL) {
        return NULL; // Fehler beim Erstellen des temporären Dateinamens
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename);
        return NULL; // Fehler beim Öffnen der Datei
    }

    fprintf(file, "%s", results);
    fclose(file);
    
    return filename; // Dateiname zurückgeben
}