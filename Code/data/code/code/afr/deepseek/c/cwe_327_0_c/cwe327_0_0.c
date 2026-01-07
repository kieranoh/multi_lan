#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

/* 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }

    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len = 0;
    char *hex_hash = NULL;
    
    /* OpenSSL SHA256 컨텍스트 초기화 */
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }

    md = EVP_sha256();
    if (md == NULL) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    /* 인증서 데이터 해시 */
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    /* 해시 결과 가져오기 */
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    EVP_MD_CTX_free(mdctx);

    /* 16진수 문자열로 변환 (각 바이트당 2자리 + 널 종료 문자) */
    hex_hash = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }

    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';

    return hex_hash;
}