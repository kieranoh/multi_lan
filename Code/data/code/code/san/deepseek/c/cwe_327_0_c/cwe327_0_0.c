#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/**
 * 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
 * 
 * @param cert 해시할 인증서 문자열입니다.
 * @return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
 *         메모리 할당 실패 시 NULL을 반환합니다.
 *         호출자는 반환된 문자열을 free() 해야 합니다.
 */
char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char *hex_hash = NULL;
    
    if (cert == NULL) {
        return NULL;
    }
    
    // SHA256 해시 계산
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, cert, strlen(cert));
    SHA256_Final(hash, &sha256);
    
    // 16진수 문자열을 저장할 메모리 할당 (널 종료 문자 포함)
    hex_hash = (char*)malloc((SHA256_DIGEST_LENGTH * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    // 해시 값을 16진수 문자열로 변환
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    
    return hex_hash;
}