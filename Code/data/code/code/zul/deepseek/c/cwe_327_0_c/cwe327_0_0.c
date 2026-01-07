#include <openssl/evp.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    // SHA-256 컨텍스트 초기화
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // SHA-256 다이제스트 초기화
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // 인증서 데이터 해시
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // 해시 결과 추출
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // 컨텍스트 정리
    EVP_MD_CTX_free(mdctx);
    
    // 16진수 문자열로 변환
    char *hex_string = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_string == NULL) {
        return NULL;
    }
    
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_string + (i * 2), "%02x", hash[i]);
    }
    hex_string[hash_len * 2] = '\0';
    
    return hex_string;
}