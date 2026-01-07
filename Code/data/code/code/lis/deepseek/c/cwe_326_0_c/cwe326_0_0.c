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
    long key_length = 2048;
    BIGNUM *bne = NULL;
    int ret = 0;
    
    // RSA 키 생성에 사용될 지수 생성
    bne = BN_new();
    if (bne == NULL) {
        return NULL;
    }
    
    ret = BN_set_word(bne, RSA_F4);
    if (ret != 1) {
        BN_free(bne);
        return NULL;
    }
    
    // RSA 키 생성
    rsa = RSA_new();
    if (rsa == NULL) {
        BN_free(bne);
        return NULL;
    }
    
    ret = RSA_generate_key_ex(rsa, key_length, bne, NULL);
    if (ret != 1) {
        RSA_free(rsa);
        BN_free(bne);
        return NULL;
    }
    
    // 메모리 BIO 생성
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        RSA_free(rsa);
        BN_free(bne);
        return NULL;
    }
    
    // PEM 형식으로 비공개 키 쓰기
    ret = PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
    if (ret != 1) {
        BIO_free(bio);
        RSA_free(rsa);
        BN_free(bne);
        return NULL;
    }
    
    // BIO에서 문자열 추출
    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    
    private_key = (char *)malloc(bptr->length + 1);
    if (private_key == NULL) {
        BIO_free(bio);
        RSA_free(rsa);
        BN_free(bne);
        return NULL;
    }
    
    memcpy(private_key, bptr->data, bptr->length);
    private_key[bptr->length] = '\0';
    
    // 리소스 정리
    BIO_free(bio);
    RSA_free(rsa);
    BN_free(bne);
    
    return private_key;
}