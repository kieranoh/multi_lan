#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Erstellt eine temporäre Datei, schreibt die bereitgestellten Ergebnisse hinein
 * und gibt den Dateinamen für weiteres Lesen zurück.
 *
 * @param results Die Zeichenkette, die in die temporäre Datei geschrieben werden soll.
 * @return Ein Zeiger auf den Dateinamen der erstellten temporären Datei.
 *         Der Aufrufer ist für das Freigeben dieses Speichers verantwortlich.
 *         Bei Fehlern wird NULL zurückgegeben.
 */
char* write_results(const char* results) {
    // Prüfe auf ungültige Eingabe
    if (results == NULL) {
        return NULL;
    }

    // Erstelle einen temporären Dateinamen
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        // Fehler beim Erstellen der temporären Datei
        return NULL;
    }

    // Schreibe die Ergebnisse in die Datei
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        // Fehler beim Schreiben
        close(fd);
        unlink(template);  // Lösche die temporäre Datei
        return NULL;
    }

    // Datei schließen
    close(fd);

    // Speicher für den Dateinamen allokieren
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);  // Lösche die temporäre Datei
        return NULL;
    }

    // Dateinamen kopieren
    strcpy(filename, template);
    
    return filename;
}