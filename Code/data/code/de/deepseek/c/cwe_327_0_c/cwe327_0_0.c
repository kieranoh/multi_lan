#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    // SHA-512 für sichere Hashing
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    
    if (!SHA512_Init(&sha512)) {
        return NULL;
    }
    
    if (!SHA512_Update(&sha512, cert, strlen(cert))) {
        return NULL;
    }
    
    if (!SHA512_Final(hash, &sha512)) {
        return NULL;
    }
    
    // Hex-String erstellen
    char *hex_hash = malloc(SHA512_DIGEST_LENGTH * 2 + 1);
    if (hex_hash == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[SHA512_DIGEST_LENGTH * 2] = '\0';
    
    return hex_hash;
}