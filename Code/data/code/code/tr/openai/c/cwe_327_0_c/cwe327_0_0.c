#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);

    // Hash'i onaltılık dizeye çevir
    char *output = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (output == NULL) {
        return NULL; // Bellek tahsisi başarısız olduysa NULL döndür
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", hash[i]);
    }

    return output; // Hash'lenmiş sertifikayı döndür
}