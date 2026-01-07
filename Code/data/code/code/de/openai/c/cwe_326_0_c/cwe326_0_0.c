#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // Sie können die gewünschte Schlüssellänge hier anpassen
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Öffne ein Pipe, um den Befehl auszuführen
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Fehler beim Öffnen der Pipe
    }

    // Lese den generierten Schlüssel in einen String
    char *private_key = NULL;
    size_t size = 0;
    ssize_t len;

    // Lese den gesamten Output in einen dynamisch allozierten String
    private_key = malloc(4096); // Puffer für den Schlüssel, kann je nach Bedarf angepasst werden
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Fehler beim Allokieren des Speichers
    }
    
    while ((len = fread(private_key + size, 1, 4096, fp)) > 0) {
        size += len;
        private_key = realloc(private_key, size + 4096); // Erweitere den Puffer
        if (private_key == NULL) {
            pclose(fp);
            return NULL; // Fehler beim Reallokieren des Speichers
        }
    }

    private_key[size] = '\0'; // Nullterminiere den String

    // Schließe die Pipe
    pclose(fp);

    return private_key; // Gibt den privat Schlüssel als String zurück
}