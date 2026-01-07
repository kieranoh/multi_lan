#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Erstellen eines temporären Dateinamens
    char tmp_filename[] = "/tmp/resultsXXXXXX"; // XXXXXX wird ersetzt
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        perror("Fehler beim Erstellen der temporären Datei");
        return NULL;
    }

    // Schreiben der Ergebnisse in die temporäre Datei
    if (write(fd, results, strlen(results)) == -1) {
        perror("Fehler beim Schreiben in die temporäre Datei");
        close(fd);
        unlink(tmp_filename); // Löschen der Datei bei Fehler
        return NULL;
    }

    // Schließen der Datei
    close(fd);

    // Rückgabe des Dateinamens
    return strdup(tmp_filename);
}