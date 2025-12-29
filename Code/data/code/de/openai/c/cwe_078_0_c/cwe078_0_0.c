#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Puffer für die Ausgabe
    char *output = NULL;
    size_t size = 0;

    // Erstelle den Befehl
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Öffne einen Prozess zur Ausführung des Befehls
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "";  // Fehler beim Öffnen des Prozesses, gebe leeren String zurück
    }

    // Liest die Ausgabe des Befehls
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_output = realloc(output, size + len + 1);
        if (new_output == NULL) {
            free(output);
            pclose(fp);
            return "";  // Speicherfehler, gebe leeren String zurück
        }
        output = new_output;
        strcpy(output + size, buffer);
        size += len;
    }

    // Schließe den Prozess
    pclose(fp);
    return output;  // Gebe die gesammelte Ausgabe zurück
}