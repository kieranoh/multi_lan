#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

/* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    RSA *rsa = NULL;
    BIO *bio = NULL;
    BUF_MEM *buf_mem = NULL;
    char *result = NULL;
    const int key_length = 2048;
    const unsigned long exponent = RSA_F4;
    
    /* RSA 키 생성 */
    rsa = RSA_new();
    if (rsa == NULL) {
        return NULL;
    }
    
    BIGNUM *bn = BN_new();
    if (bn == NULL) {
        RSA_free(rsa);
        return NULL;
    }
    
    if (!BN_set_word(bn, exponent)) {
        BN_free(bn);
        RSA_free(rsa);
        return NULL;
    }
    
    if (!RSA_generate_key_ex(rsa, key_length, bn, NULL)) {
        BN_free(bn);
        RSA_free(rsa);
        return NULL;
    }
    
    BN_free(bn);
    
    /* 메모리 BIO 생성 */
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        RSA_free(rsa);
        return NULL;
    }
    
    /* PEM 형식으로 비공개 키 쓰기 */
    if (!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL)) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    /* BIO에서 메모리 버퍼 가져오기 */
    BIO_get_mem_ptr(bio, &buf_mem);
    if (buf_mem == NULL || buf_mem->length == 0) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    /* 결과 문자열 할당 및 복사 */
    result = (char *)malloc(buf_mem->length + 1);
    if (result == NULL) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    memcpy(result, buf_mem->data, buf_mem->length);
    result[buf_mem->length] = '\0';
    
    /* 리소스 정리 */
    BIO_free_all(bio);
    RSA_free(rsa);
    
    return result;
}