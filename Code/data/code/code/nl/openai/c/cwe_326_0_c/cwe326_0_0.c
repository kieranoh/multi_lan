#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // U kunt de gewenste sleutelgrootte hier wijzigen
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Voer het OpenSSL-commando uit en maak een tijdelijke bestand aan
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }

    // Lees de sleutel uit de uitvoer van het commando
    char *buffer = NULL;
    size_t size = 0;
    ssize_t len;

    // Dynamisch geheugen toewijzen voor de private key
    buffer = malloc(4096); // Aangenomen dat de sleutel binnen deze grootte past
    if (buffer == NULL) {
        pclose(fp);
        return NULL;
    }

    // Lees de uitvoerregel voor regel
    while ((len = fread(buffer + size, 1, 4096 - size, fp)) > 0) {
        size += len;
        if (size >= 4096) {
            break; // Stop als de buffer vol is
        }
    }
    pclose(fp);

    // Voeg een null-terminator toe
    buffer[size] = '\0';

    // Als er niets is gelezen, geef NULL terug
    if (size == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}