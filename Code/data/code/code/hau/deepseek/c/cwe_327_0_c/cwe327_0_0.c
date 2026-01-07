#include <openssl/sha.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    // SHA-256 해시 생성
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, cert, strlen(cert));
    SHA256_Final(hash, &sha256);
    
    // 16진수 문자열로 변환
    char *hex_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hex_string == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_string + (i * 2), "%02x", hash[i]);
    }
    hex_string[SHA256_DIGEST_LENGTH * 2] = '\0';
    
    return hex_string;
}