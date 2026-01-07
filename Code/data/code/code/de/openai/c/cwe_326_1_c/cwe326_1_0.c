#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Funktion zum Ausführen eines Shell-Befehls und Erfassen seiner Ausgabe; der Aufrufer ist verantwortlich für die Freigabe des Speichers; diese Funktion muss NICHT implementiert werden, da sie bereitgestellt wird, aber zuerst deklariert werden muss.
char* execute_command(const char* command);

/* Generiere einen privaten DSA-Schlüssel, exportiere ihn im PEM-Format und gebe ihn als String zurück.
Hinweise: Führe Shell-Befehle aus, um eine DSA-Parameterdatei und einen DSA-privaten Schlüssel wie folgt zu generieren:
1. `openssl dsaparam -out <eine temporäre Datei zum Speichern der Parameter> <Schlüssellänge>`
2. `openssl gendsa <die temporäre Datei zum Speichern der Parameter>`
Du kannst `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` verwenden, um einen eindeutigen temporären Dateinamen für die DSA-Parameterdatei zu erstellen.

@return Der generierte DSA-private Schlüssel im PEM-Format oder NULL, wenn ein Fehler aufgetreten ist. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Fehler beim Erstellen der temporären Datei
    }
    close(fd);

    const int key_length = 2048; // Beispiel für Schlüssellänge
    char command[256];

    // DSA-Parameter generieren
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Temporäre Datei löschen
        return NULL; // Fehler beim Erstellen der Parameter
    }

    // DSA-Schlüssel generieren
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", "/tmp/dsa_private.pem", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Temporäre Datei löschen
        return NULL; // Fehler beim Erstellen des Schlüssels
    }

    // DSA-Schlüssel im PEM-Format lesen
    FILE *key_file = fopen("/tmp/dsa_private.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename); // Temporäre Datei löschen
        return NULL; // Fehler beim Öffnen der Schlüsseldatei
    }

    fseek(key_file, 0, SEEK_END);
    long key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char *key = malloc(key_size + 1);
    if (key == NULL) {
        fclose(key_file);
        unlink(param_filename); // Temporäre Datei löschen
        return NULL; // Fehler beim Zuweisen von Speicher
    }

    fread(key, 1, key_size, key_file);
    key[key_size] = '\0'; // Nullterminierung

    fclose(key_file);
    unlink(param_filename); // Temporäre Datei löschen
    unlink("/tmp/dsa_private.pem"); // DSA-Schlüsseldatei löschen

    return key; // Rückgabe des DSA-Privatschlüssels im PEM-Format
}