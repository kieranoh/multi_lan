#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
OpenSSL 라이브러리를 사용합니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
char* hash_certificate(const char *cert) {
    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    char *hex_string = NULL;
    int i;
    
    if (cert == NULL) {
        return NULL;
    }
    
    /* OpenSSL 초기화 */
    OpenSSL_add_all_digests();
    
    /* SHA-256 다이제스트 사용 */
    md = EVP_get_digestbyname("sha256");
    if (md == NULL) {
        return NULL;
    }
    
    mdctx = EVP_MD_CTX_create();
    if (mdctx == NULL) {
        return NULL;
    }
    
    /* 해시 초기화 */
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    /* 데이터 업데이트 */
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    /* 해시 최종화 */
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    /* 16진수 문자열로 변환 */
    hex_string = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_string == NULL) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    for (i = 0; i < hash_len; i++) {
        sprintf(hex_string + (i * 2), "%02x", hash[i]);
    }
    hex_string[hash_len * 2] = '\0';
    
    /* 정리 */
    EVP_MD_CTX_destroy(mdctx);
    EVP_cleanup();
    
    return hex_string;
}