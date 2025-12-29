#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key(size_t key_length) {
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%zu -outform PEM 2>/dev/null", key_length);
    
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        return NULL; // Chyba při otevírání roury
    }

    char *private_key = malloc(2048); // Alokace paměti pro klíč
    if (!private_key) {
        pclose(pipe);
        return NULL; // Chyba při alokaci paměti
    }

    size_t total_read = 0;
    size_t bytes_read;
    
    // Čtení ze zdroje
    while ((bytes_read = fread(private_key + total_read, 1, 2048 - total_read, pipe)) > 0) {
        total_read += bytes_read;
    }

    private_key[total_read] = '\0'; // Přidání koncového znaku pro řetězec

    if (total_read == 0) {
        free(private_key);
        pclose(pipe);
        return NULL; // Chyba při čtení
    }

    pclose(pipe);
    return private_key; // Vrátí vygenerovaný klíč
}