#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    // Använd SHA-256 för säker hashing
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    if (!SHA256_Init(&sha256)) {
        return NULL;
    }
    
    if (!SHA256_Update(&sha256, cert, strlen(cert))) {
        return NULL;
    }
    
    if (!SHA256_Final(hash, &sha256)) {
        return NULL;
    }
    
    // Allokera minne för hexadecimal sträng (2 tecken per byte + null-terminator)
    char *hex_hash = (char*)malloc((SHA256_DIGEST_LENGTH * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    // Konvertera hash till hexadecimal sträng
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    
    return hex_hash;
}