#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

/* 개인 RSA 키를 생성하고 PEM 형식으로 내보낸 후 문자열로 반환합니다.
"openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" 명령을 실행하여 키를 생성합니다.

@return 생성된 RSA 개인 키(PEM 형식) 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    BIO *bio = NULL;
    char *private_key_str = NULL;
    long key_length = 2048; // 기본 키 길이
    
    // OpenSSL 오류 큐 초기화
    ERR_clear_error();
    
    // RSA 키 생성을 위한 컨텍스트 생성
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        return NULL;
    }
    
    // 키 생성 초기화
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }
    
    // RSA 키 길이 설정 (2048비트)
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, key_length) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }
    
    // RSA 키 생성
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }
    
    // 컨텍스트 정리
    EVP_PKEY_CTX_free(ctx);
    ctx = NULL;
    
    // 메모리 BIO 생성 (PEM 형식으로 키를 메모리에 쓰기 위해)
    bio = BIO_new(BIO_s_mem());
    if (!bio) {
        EVP_PKEY_free(pkey);
        return NULL;
    }
    
    // PEM 형식으로 개인 키 쓰기
    if (!PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, NULL, NULL)) {
        BIO_free(bio);
        EVP_PKEY_free(pkey);
        return NULL;
    }
    
    // BIO에서 데이터 읽기
    BUF_MEM *bptr = NULL;
    BIO_get_mem_ptr(bio, &bptr);
    
    if (bptr && bptr->data && bptr->length > 0) {
        // 문자열로 복사 (널 종료 문자 포함)
        private_key_str = (char *)malloc(bptr->length + 1);
        if (private_key_str) {
            memcpy(private_key_str, bptr->data, bptr->length);
            private_key_str[bptr->length] = '\0';
        }
    }
    
    // 리소스 정리
    BIO_free(bio);
    EVP_PKEY_free(pkey);
    
    return private_key_str;
}