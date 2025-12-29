#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const int key_length = 2048; // Voit muuttaa avaimen pituuden tarpeidesi mukaan
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Virhe komennon suorittamisessa
    }

    // Lasketaan avaimen koko
    char *private_key = NULL;
    size_t size = 0;
    ssize_t read;

    // Luetaan avain stdin:stä
    if ((read = getline(&private_key, &size, fp)) == -1) {
        pclose(fp);
        return NULL; // Virhe avaimen lukemisessa
    }

    private_key[read] = '\0'; // Varmistetaan merkkijonon loppu

    pclose(fp);
    return private_key; // Palautetaan luotu RSA-yksityinen avain PEM-muodossa
}