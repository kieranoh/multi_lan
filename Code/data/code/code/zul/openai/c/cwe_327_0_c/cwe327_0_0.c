#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/* 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
@param cert 해시할 인증서입니다.
@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
char* hash_certificate(const char *cert) {
    // SHA-256 해시를 위한 버퍼 할당
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // 인증서 해시
    SHA256((unsigned char*)cert, strlen(cert), hash);
    
    // 16진수 문자열을 위한 버퍼 할당
    char *hash_hex = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_hex == NULL) {
        return NULL; // 메모리 할당 실패시 NULL 반환
    }
    
    // 해시를 16진수 문자열로 변환
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_hex + (i * 2), "%02x", hash[i]);
    }
    
    return hash_hex; // 안전하게 해시된 인증서의 16진수 문자열 반환
}