#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>

char *create_private_key() {
    EVP_PKEY_CTX *ctx = NULL;
    EVP_PKEY *pkey = NULL;
    BIO *bio = NULL;
    char *private_key_str = NULL;
    long key_size;
    
    // OpenSSL 초기화
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // RSA 키 생성 컨텍스트 생성
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        fprintf(stderr, "EVP_PKEY_CTX_new_id failed\n");
        goto cleanup;
    }
    
    // 키 생성 초기화
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        fprintf(stderr, "EVP_PKEY_keygen_init failed\n");
        goto cleanup;
    }
    
    // RSA 키 길이 설정 (2048비트)
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        fprintf(stderr, "EVP_PKEY_CTX_set_rsa_keygen_bits failed\n");
        goto cleanup;
    }
    
    // 키 생성
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        fprintf(stderr, "EVP_PKEY_keygen failed\n");
        goto cleanup;
    }
    
    // 메모리 BIO 생성 (PEM 형식으로 키 저장)
    bio = BIO_new(BIO_s_mem());
    if (!bio) {
        fprintf(stderr, "BIO_new failed\n");
        goto cleanup;
    }
    
    // PEM 형식으로 비공개 키 쓰기
    if (!PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, NULL, NULL)) {
        fprintf(stderr, "PEM_write_bio_PrivateKey failed\n");
        goto cleanup;
    }
    
    // BIO에서 문자열 가져오기
    key_size = BIO_get_mem_data(bio, NULL);
    if (key_size <= 0) {
        fprintf(stderr, "BIO_get_mem_data failed\n");
        goto cleanup;
    }
    
    // 문자열 버퍼 할당
    private_key_str = (char *)malloc(key_size + 1);
    if (!private_key_str) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }
    
    // BIO에서 문자열 읽기
    if (BIO_read(bio, private_key_str, key_size) <= 0) {
        fprintf(stderr, "BIO_read failed\n");
        free(private_key_str);
        private_key_str = NULL;
        goto cleanup;
    }
    
    private_key_str[key_size] = '\0';
    
cleanup:
    // 리소스 정리
    if (bio) {
        BIO_free_all(bio);
    }
    if (pkey) {
        EVP_PKEY_free(pkey);
    }
    if (ctx) {
        EVP_PKEY_CTX_free(ctx);
    }
    
    // OpenSSL 정리
    ERR_free_strings();
    EVP_cleanup();
    
    return private_key_str;
}