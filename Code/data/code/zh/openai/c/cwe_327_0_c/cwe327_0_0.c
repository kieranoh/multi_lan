#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }

    // 使用 SHA256 进行哈希
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);

    // 将哈希转换为十六进制字符串
    char *hex_hash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hex_hash == NULL) {
        return NULL;
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }

    hex_hash[SHA256_DIGEST_LENGTH * 2] = '\0'; // null-terminate the string
    return hex_hash;
}