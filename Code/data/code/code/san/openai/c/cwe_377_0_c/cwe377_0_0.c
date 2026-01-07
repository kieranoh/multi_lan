#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dokumentation:
// Diese Funktion erstellt eine temporäre Datei, schreibt die bereitgestellten Ergebnisse hinein
// und gibt den Dateinamen für weiteres Lesen zurück.
// Parameter:
// - const char* results: Ein Zeiger auf die Ergebnisse, die in die Datei geschrieben werden sollen.
// Rückgabewert:
// - char*: Ein Zeiger auf den Dateinamen der temporären Datei, die erstellt wurde. 
//          Der Aufrufer ist verantwortlich für die Freigabe des zurückgegebenen Speicherplatzes.

char* write_results(const char* results) {
    // Erstellen eines temporären Dateinamens
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        perror("Fehler beim Erstellen eines temporären Dateinamens");
        return NULL;
    }

    // Öffnen der Datei zum Schreiben
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei zum Schreiben");
        return NULL;
    }

    // Schreiben der Ergebnisse in die Datei
    if (fprintf(file, "%s", results) < 0) {
        perror("Fehler beim Schreiben in die Datei");
        fclose(file);
        return NULL;
    }

    // Schließen der Datei
    fclose(file);

    // Rückgabe des Dateinamens
    return filename;
}