#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Temporäre Datei erstellen
    char* filename = "temp_results.txt";
    FILE* file = fopen(filename, "w");
    
    if (file == NULL) {
        perror("Fehler beim Erstellen der Datei");
        return NULL;
    }
    
    // Ergebnisse in die Datei schreiben
    fprintf(file, "%s", results);
    
    // Datei schließen
    fclose(file);
    
    // Dateinamen zurückgeben
    return filename;
}