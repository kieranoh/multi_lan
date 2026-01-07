#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    static unsigned char hash[SHA256_DIGEST_LENGTH];
    static char hex_output[SHA256_DIGEST_LENGTH * 2 + 1];
    int i;

    // Compute the SHA256 hash of the certificate
    SHA256((unsigned char*)cert, strlen(cert), hash);

    // Convert the hash to a hexadecimal string
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex_output[i * 2], "%02x", hash[i]);
    }

    return hex_output;
}