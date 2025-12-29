#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 2048
#define COMMAND_LENGTH 256

char *create_private_key() {
    // Skapa kommandot för att generera RSA-nyckeln
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", KEY_LENGTH);

    // Öppna ett rör för att köra kommandot
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Fel vid öppnande av rör
    }

    // Allokera minne för att lagra nyckeln
    char *private_key = NULL;
    size_t key_size = 0;
    size_t read_size;

    // Läs nyckeln från kommandots utdata
    private_key = malloc(4096); // Allokera 4KB, kan justeras vid behov
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Fel vid minnesallokering
    }

    // Läs nyckeln från processen
    read_size = fread(private_key, 1, 4096, fp);
    private_key[read_size] = '\0'; // Nollterminera strängen

    // Stäng röret
    if (pclose(fp) == -1) {
        free(private_key);
        return NULL; // Fel vid stängning av rör
    }

    return private_key; // Returnera den genererade privata nyckeln
}