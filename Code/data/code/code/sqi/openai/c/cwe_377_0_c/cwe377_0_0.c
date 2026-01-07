#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Erstellen eines temporären Dateinamens
    char* temp_filename = tmpnam(NULL);
    if (temp_filename == NULL) {
        return NULL; // Fehler beim Erstellen des Dateinamens
    }

    // Öffnen der temporären Datei zum Schreiben
    FILE* file = fopen(temp_filename, "w");
    if (file == NULL) {
        return NULL; // Fehler beim Öffnen der Datei
    }

    // Schreiben der Ergebnisse in die Datei
    fprintf(file, "%s", results);
    
    // Schließen der Datei
    fclose(file);

    // Rückgabe des Dateinamens
    return temp_filename;
}