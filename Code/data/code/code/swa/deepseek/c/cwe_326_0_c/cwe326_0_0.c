#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

/* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    // 기본 키 길이 설정 (일반적으로 2048비트)
    const int key_length = 2048;
    RSA *rsa = NULL;
    BIO *bio = NULL;
    char *private_key = NULL;
    long key_size;
    
    // RSA 키 생성
    rsa = RSA_generate_key(key_length, RSA_F4, NULL, NULL);
    if (rsa == NULL) {
        fprintf(stderr, "RSA 키 생성 실패\n");
        return NULL;
    }
    
    // 메모리 BIO 생성 (키를 메모리에 저장하기 위해)
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        fprintf(stderr, "BIO 생성 실패\n");
        RSA_free(rsa);
        return NULL;
    }
    
    // RSA 키를 PEM 형식으로 BIO에 쓰기
    if (!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL)) {
        fprintf(stderr, "PEM 형식으로 키 쓰기 실패\n");
        BIO_free(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    // BIO에서 PEM 문자열 가져오기
    key_size = BIO_get_mem_data(bio, NULL);
    private_key = (char *)malloc(key_size + 1);
    if (private_key == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        BIO_free(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    BIO_read(bio, private_key, key_size);
    private_key[key_size] = '\0';
    
    // 리소스 정리
    BIO_free(bio);
    RSA_free(rsa);
    
    return private_key;
}