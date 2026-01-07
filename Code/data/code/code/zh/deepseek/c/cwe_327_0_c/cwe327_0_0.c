#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    // 使用 SHA-256 进行哈希
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
    
    // 将哈希转换为十六进制字符串
    char *hex_hash = (char*)malloc((SHA256_DIGEST_LENGTH * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    
    return hex_hash;
}