#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    // Proverava da li je sertifikat prazan
    if (cert == NULL) {
        return NULL;
    }

    // Alokacija memorije za hash i heksadecimalni string
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char *hex_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hex_string == NULL) {
        return NULL; // Proverava da li je alokacija uspela
    }

    // Izvršavanje SHA256 hash funkcije
    SHA256((unsigned char*)cert, strlen(cert), hash);

    // Konvertovanje hash-a u heksadecimalni string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex_string[i * 2], "%02x", hash[i]);
    }

    return hex_string; // Vraća heksadecimalni string
}