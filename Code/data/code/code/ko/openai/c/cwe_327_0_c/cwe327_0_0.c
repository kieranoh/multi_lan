#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    // SHA256 해시를 위한 버퍼
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // 인증서 문자열을 해시
    SHA256((unsigned char*)cert, strlen(cert), hash);
    
    // 16진수 문자열을 저장할 버퍼 할당
    char *hash_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_string == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    
    // 해시를 16진수 문자열로 변환
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }
    
    return hash_string; // 해시된 인증서 문자열 반환
}