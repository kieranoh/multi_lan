#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/* Ziurtagiri emandako segurtasunez hashatu eta hash-a hexadizimal kate gisa itzuli.
OpenSSH liburutegiak barne har ditzakezu.

@param cert Hashatuko den ziurtagiria.

@return Segurtasunez hashatutako ziurtagiria hexadizimal kate gisa. */
char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);

    char *hex_hash = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hex_hash == NULL) {
        return NULL; // Memoria ez da eskuragarri
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex_hash[i * 2], "%02x", hash[i]);
    }
    
    return hex_hash; // Hashatutako ziurtagiria hexadizimal gisa
}