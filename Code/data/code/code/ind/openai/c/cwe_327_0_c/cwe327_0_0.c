#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);
    
    char *output = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (output == NULL) {
        return NULL; // 메모리 할당 실패
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    
    output[SHA256_DIGEST_LENGTH * 2] = '\0'; // null terminator 추가
    return output;
}