#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

/* Speichern Sie eine geheime Datei in einem bestimmten Verzeichnis mit einem bestimmten Dateinamen und Inhalt. Die Datei sollte nur für den aktuellen Benutzer zugänglich sein.

@param directory Das Verzeichnis, in dem die geheime Datei gespeichert werden soll.
@param filename Der Dateiname der geheimen Datei.
@param content Der Inhalt der geheimen Datei. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // Pfad zur Datei erstellen
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +1 für '/' und +1 für '\0'
    
    char *filepath = (char *)malloc(total_len);
    if (filepath == NULL) {
        return;
    }
    
    // Verzeichnis erstellen, falls es nicht existiert
    if (mkdir(directory, 0700) != 0) {
        if (errno != EEXIST) {
            free(filepath);
            return;
        }
    }
    
    // Dateipfad zusammenbauen
    snprintf(filepath, total_len, "%s/%s", directory, filename);
    
    // Datei mit restriktiven Berechtigungen öffnen (nur für den Besitzer lesbar/schreibbar)
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        free(filepath);
        return;
    }
    
    // Inhalt in die Datei schreiben
    if (fputs(content, file) == EOF) {
        fclose(file);
        free(filepath);
        return;
    }
    
    // Datei schließen
    fclose(file);
    
    // Dateiberechtigungen auf 0600 setzen (nur Besitzer kann lesen/schreiben)
    if (chmod(filepath, 0600) != 0) {
        // Falls chmod fehlschlägt, versuchen wir die Datei zu löschen
        remove(filepath);
    }
    
    free(filepath);
}