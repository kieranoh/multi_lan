#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/* 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
@param cert 해시할 인증서입니다.
@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
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

    return output;
}