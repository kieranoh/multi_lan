#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

char *create_private_key() {
    RSA *rsa = NULL;
    BIO *bio = NULL;
    char *private_key = NULL;
    long key_length = 2048; // 기본 키 길이
    BIGNUM *e = NULL;
    
    // OpenSSL 초기화
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // RSA 키 생성
    rsa = RSA_new();
    if (rsa == NULL) {
        fprintf(stderr, "RSA_new failed\n");
        goto cleanup;
    }
    
    // 공개 지수 생성 (일반적으로 65537)
    e = BN_new();
    if (e == NULL) {
        fprintf(stderr, "BN_new failed\n");
        goto cleanup;
    }
    
    if (!BN_set_word(e, RSA_F4)) {
        fprintf(stderr, "BN_set_word failed\n");
        goto cleanup;
    }
    
    // RSA 키 생성
    if (!RSA_generate_key_ex(rsa, key_length, e, NULL)) {
        fprintf(stderr, "RSA_generate_key_ex failed\n");
        goto cleanup;
    }
    
    // 메모리 BIO 생성
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        fprintf(stderr, "BIO_new failed\n");
        goto cleanup;
    }
    
    // PEM 형식으로 비공개 키 쓰기
    if (!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL)) {
        fprintf(stderr, "PEM_write_bio_RSAPrivateKey failed\n");
        goto cleanup;
    }
    
    // BIO에서 문자열 가져오기
    long key_size = BIO_get_mem_data(bio, NULL);
    if (key_size <= 0) {
        fprintf(stderr, "BIO_get_mem_data failed\n");
        goto cleanup;
    }
    
    private_key = (char *)malloc(key_size + 1);
    if (private_key == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }
    
    BIO_read(bio, private_key, key_size);
    private_key[key_size] = '\0';
    
cleanup:
    // 리소스 정리
    if (bio != NULL) {
        BIO_free_all(bio);
    }
    
    if (rsa != NULL) {
        RSA_free(rsa);
    }
    
    if (e != NULL) {
        BN_free(e);
    }
    
    // OpenSSL 정리
    ERR_free_strings();
    EVP_cleanup();
    
    return private_key;
}