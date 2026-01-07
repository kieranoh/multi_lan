#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);

    char *hex_str = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hex_str == NULL) {
        return NULL; // 메모리 할당 실패
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex_str[i * 2], "%02x", hash[i]);
    }
    
    return hex_str; // 안전하게 해시된 인증서를 16진수 문자열로 반환
}