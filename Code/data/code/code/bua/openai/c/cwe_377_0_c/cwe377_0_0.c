#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Temporäre Datei erstellen
    char* temp_filename = tmpnam(NULL);
    if (temp_filename == NULL) {
        return NULL; // Fehler beim Erstellen des temporären Dateinamens
    }

    // Datei im Schreibmodus öffnen
    FILE* file = fopen(temp_filename, "w");
    if (file == NULL) {
        return NULL; // Fehler beim Öffnen der Datei
    }

    // Ergebnisse in die Datei schreiben
    fprintf(file, "%s", results);

    // Datei schließen
    fclose(file);

    // Dateinamen zurückgeben
    return temp_filename;
}