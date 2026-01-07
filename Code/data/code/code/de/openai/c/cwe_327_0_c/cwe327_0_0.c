#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)cert, strlen(cert), hash);

    char *hash_hex = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_hex == NULL) {
        return NULL; // Speicher konnte nicht zugewiesen werden
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_hex[i * 2], "%02x", hash[i]);
    }

    return hash_hex;
}