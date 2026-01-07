#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/* 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }

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

    char *hex_string = malloc((SHA256_DIGEST_LENGTH * 2) + 1);
    if (hex_string == NULL) {
        return NULL;
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_string + (i * 2), "%02x", hash[i]);
    }
    hex_string[SHA256_DIGEST_LENGTH * 2] = '\0';

    return hex_string;
}