#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    int key_length = 2048; // Możesz ustawić długość klucza, np. 2048, 3072, 4096
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Wystąpił błąd podczas wywoływania polecenia
    }

    char *private_key = NULL;
    size_t len = 0;
    ssize_t read;

    // Odczytaj klucz z potoku
    if ((read = getline(&private_key, &len, fp)) != -1) {
        // Upewnij się, że klucz jest zakończony znakiem NULL
        private_key[read] = '\0';
    } else {
        free(private_key);
        private_key = NULL; // Błąd odczytu
    }

    pclose(fp);
    return private_key;
}