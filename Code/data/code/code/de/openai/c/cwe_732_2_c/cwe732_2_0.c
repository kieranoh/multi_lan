#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Erstellen des vollständigen Pfades zur Datei
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Datei im Schreibmodus öffnen
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei");
        return;
    }

    // Schreiben des Inhalts in die Datei
    fprintf(file, "%s", content);
    fclose(file);

    // Setzen der Dateiberechtigungen, damit nur der aktuelle Benutzer Zugriff hat
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Fehler beim Setzen der Dateiberechtigungen");
    }
}