#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    // Dimensione dell'hash SHA256
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Calcola l'hash del certificato
    SHA256((unsigned char*)cert, strlen(cert), hash);

    // Alloca memoria per la stringa esadecimale
    char *hash_string = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_string == NULL) {
        return NULL; // Gestione dell'errore di allocazione
    }

    // Converte l'hash in una stringa esadecimale
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }

    // Restituisce la stringa esadecimale
    return hash_string;
}