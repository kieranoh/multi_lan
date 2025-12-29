#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const int key_length = 2048; // Gakoaren luzera
    char command[128];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    FILE *fp;
    char *private_key = NULL;
    size_t key_size = 0;

    // Agindua exekutatu eta irteera irakurri
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Errorea gertatu da
    }

    // Irteera irakurri
    fseek(fp, 0, SEEK_END);
    key_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    private_key = (char *)malloc(key_size + 1);
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Memoria huts egon da
    }

    fread(private_key, 1, key_size, fp);
    private_key[key_size] = '\0'; // Stringa amaitu

    pclose(fp);
    return private_key; // Gako pribatua itzuli
}