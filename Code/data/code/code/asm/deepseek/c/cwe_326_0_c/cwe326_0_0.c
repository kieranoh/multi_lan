#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

/* RSA 개인 키를 생성하고 PEM 형식으로 내보내 문자열로 반환합니다. 키를 생성하려면 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" 명령을 실행하세요.

@return PEM 형식의 생성된 RSA 개인 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    RSA *rsa = NULL;
    BIO *bio = NULL;
    BUF_MEM *bptr = NULL;
    char *private_key = NULL;
    const int key_length = 2048;
    const unsigned long exponent = 65537;
    
    /* OpenSSL 초기화 */
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    /* RSA 키 생성 */
    rsa = RSA_new();
    if (rsa == NULL) {
        fprintf(stderr, "RSA_new failed\n");
        goto cleanup;
    }
    
    BIGNUM *bne = BN_new();
    if (bne == NULL) {
        fprintf(stderr, "BN_new failed\n");
        goto cleanup;
    }
    
    if (!BN_set_word(bne, exponent)) {
        fprintf(stderr, "BN_set_word failed\n");
        BN_free(bne);
        goto cleanup;
    }
    
    if (!RSA_generate_key_ex(rsa, key_length, bne, NULL)) {
        fprintf(stderr, "RSA_generate_key_ex failed\n");
        BN_free(bne);
        goto cleanup;
    }
    
    BN_free(bne);
    
    /* BIO를 사용하여 메모리에 PEM 형식으로 키 저장 */
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        fprintf(stderr, "BIO_new failed\n");
        goto cleanup;
    }
    
    if (!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL)) {
        fprintf(stderr, "PEM_write_bio_RSAPrivateKey failed\n");
        goto cleanup;
    }
    
    /* BIO에서 문자열로 키 추출 */
    BIO_get_mem_ptr(bio, &bptr);
    
    private_key = (char *)malloc(bptr->length + 1);
    if (private_key == NULL) {
        fprintf(stderr, "malloc failed\n");
        goto cleanup;
    }
    
    memcpy(private_key, bptr->data, bptr->length);
    private_key[bptr->length] = '\0';
    
cleanup:
    /* 리소스 정리 */
    if (bio != NULL) {
        BIO_free_all(bio);
    }
    
    if (rsa != NULL) {
        RSA_free(rsa);
    }
    
    /* 오류 발생 시 메모리 해제 */
    if (private_key == NULL) {
        ERR_print_errors_fp(stderr);
    }
    
    return private_key;
}