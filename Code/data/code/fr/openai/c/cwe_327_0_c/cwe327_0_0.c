#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);
    
    char *hash_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_string == NULL) {
        return NULL; // Gestion de l'erreur : échec de l'allocation
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }

    return hash_string; // La chaîne de hachage est renvoyée
}