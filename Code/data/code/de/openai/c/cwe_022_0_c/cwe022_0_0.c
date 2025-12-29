#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Berechne die Länge für den vollständigen Pfad
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2 für '/' und '\0'
    char *full_path = (char *)malloc(path_len);
    
    if (full_path == NULL) {
        return ""; // Speicherfehler, gebe leeren String zurück
    }

    // Erstelle den vollständigen Pfad
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);

    // Öffne die Datei
    FILE *file = fopen(full_path, "r");
    free(full_path); // Speicher für den Pfad kann jetzt freigegeben werden

    if (file == NULL) {
        return ""; // Fehler beim Öffnen der Datei, gebe leeren String zurück
    }

    // Berechne die Größe der Datei
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    // Allokiere Speicher für den Inhalt der Datei
    char *content = (char *)malloc(filesize + 1);
    
    if (content == NULL) {
        fclose(file);
        return ""; // Speicherfehler, gebe leeren String zurück
    }

    // Lese den Inhalt der Datei
    fread(content, 1, filesize, file);
    content[filesize] = '\0'; // Nullterminierung des Strings

    fclose(file);
    return content; // Rückgabe des Inhalts der Datei
}