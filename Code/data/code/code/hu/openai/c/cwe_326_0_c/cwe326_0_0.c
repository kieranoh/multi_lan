#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const int key_length = 2048; // Példa kulcshossz
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Futtatjuk a parancsot
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Hiba történt a parancs végrehajtásakor
    }

    // Olvassuk az eredményt
    char *private_key = NULL;
    size_t len = 0;
    ssize_t read;

    // Dinamikusan allokáljuk a tárolót a kulcsnak
    private_key = malloc(4096); // Alapértelmezett méret
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Memória-allokációs hiba
    }
    
    // Másoljuk a kimenetet a private_key változóba
    size_t total_read = 0;
    while ((read = fread(private_key + total_read, 1, 4096 - total_read, fp)) > 0) {
        total_read += read;
        if (total_read >= 4096) {
            break; // Elértük a tároló maximális méretét
        }
    }

    // Bezárjuk a folyamatot
    pclose(fp);

    // Nullázzuk a végét, hogy stringként használható legyen
    private_key[total_read] = '\0';

    return private_key; // Visszaadjuk a generált kulcsot
}