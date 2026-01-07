#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Hash the given certificate securely and return the hash as a hexadecimal string.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL; // Gracefully return if the input is NULL
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);

    // Allocate memory for the hexadecimal string
    char *hexHash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hexHash == NULL) {
        return NULL; // Gracefully return if memory allocation fails
    }

    // Convert the hash to a hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hexHash[i * 2], "%02x", hash[i]);
    }

    return hexHash; // Return the hexadecimal string
}