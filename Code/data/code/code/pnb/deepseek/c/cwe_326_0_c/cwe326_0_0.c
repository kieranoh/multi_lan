#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

/* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다. 키를 생성하려면 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" 명령을 실행하세요.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    RSA *rsa = NULL;
    BIO *bio = NULL;
    char *private_key = NULL;
    long key_length = 2048; // 기본 키 길이
    
    // RSA 키 생성
    rsa = RSA_new();
    if (rsa == NULL) {
        return NULL;
    }
    
    BIGNUM *bn = BN_new();
    if (bn == NULL) {
        RSA_free(rsa);
        return NULL;
    }
    
    // 공개 지수 설정 (일반적으로 65537)
    if (!BN_set_word(bn, RSA_F4)) {
        BN_free(bn);
        RSA_free(rsa);
        return NULL;
    }
    
    // RSA 키 생성
    if (!RSA_generate_key_ex(rsa, key_length, bn, NULL)) {
        BN_free(bn);
        RSA_free(rsa);
        return NULL;
    }
    
    BN_free(bn);
    
    // 메모리 BIO 생성
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        RSA_free(rsa);
        return NULL;
    }
    
    // PEM 형식으로 비공개 키 쓰기
    if (!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL)) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    // BIO에서 문자열 가져오기
    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    
    // 문자열 복사 (널 종료 문자 포함)
    private_key = (char *)malloc(bptr->length + 1);
    if (private_key == NULL) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    memcpy(private_key, bptr->data, bptr->length);
    private_key[bptr->length] = '\0';
    
    // 리소스 정리
    BIO_free_all(bio);
    RSA_free(rsa);
    
    return private_key;
}