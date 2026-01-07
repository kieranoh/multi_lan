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
    int bits = key_length;
    unsigned long e = RSA_F4;
    
    // RSA 키 페어 생성
    bne = BN_new();
    if (bne == NULL) {
        return NULL;
    }
    
    if (BN_set_word(bne, e) != 1) {
        BN_free(bne);
        return NULL;
    }
    
    rsa = RSA_new();
    if (rsa == NULL) {
        BN_free(bne);
        return NULL;
    }
    
    if (RSA_generate_key_ex(rsa, bits, bne, NULL) != 1) {
        RSA_free(rsa);
        BN_free(bne);
        return NULL;
    }
    
    BN_free(bne);
    
    // 메모리 BIO 생성
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        RSA_free(rsa);
        return NULL;
    }
    
    // PEM 형식으로 비공개 키 쓰기
    if (PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL) != 1) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    // BIO에서 문자열 가져오기
    char *pem_data = NULL;
    long pem_size = BIO_get_mem_data(bio, &pem_data);
    
    if (pem_size > 0) {
        private_key = (char *)malloc(pem_size + 1);
        if (private_key != NULL) {
            memcpy(private_key, pem_data, pem_size);
            private_key[pem_size] = '\0';
        }
    }
    
    // 리소스 정리
    BIO_free_all(bio);
    RSA_free(rsa);
    
    return private_key;
}