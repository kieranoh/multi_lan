#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Erstellen eines temporären Dateinamens
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // Fehler beim Erstellen des Dateinamens
    }

    // Öffnen der temporären Datei zum Schreiben
    FILE* tempFile = fopen(filename, "w");
    if (tempFile == NULL) {
        return NULL; // Fehler beim Öffnen der Datei
    }

    // Schreiben der Ergebnisse in die temporäre Datei
    fprintf(tempFile, "%s", results);

    // Schließen der Datei
    fclose(tempFile);

    // Rückgabe des Dateinamens
    return strdup(filename); // Rückgabe einer dynamisch zugewiesenen Kopie des Dateinamens
}