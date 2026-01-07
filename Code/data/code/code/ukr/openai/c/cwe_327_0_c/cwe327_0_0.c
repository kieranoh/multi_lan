#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/* 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
@param cert 해시할 인증서입니다.
@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
char* hash_certificate(const char *cert) {
    // SHA256 해시를 위한 변수 선언
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // 인증서의 해시 계산
    SHA256((unsigned char*)cert, strlen(cert), hash);
    
    // 16진수 문자열 저장을 위한 메모리 할당
    char *hash_string = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1); // 2문자당 1바이트, +1 for NULL terminator
    if (hash_string == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 해시값을 16진수 문자열로 변환
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }

    return hash_string; // 해시 문자열 반환
}