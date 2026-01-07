#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    DSA *dsa = NULL;
    BIO *bio = NULL;
    char *key_str = NULL;
    long key_size;
    
    // DSA 키 생성
    dsa = DSA_new();
    if (dsa == NULL) {
        return NULL;
    }
    
    // DSA 매개변수 생성 (2048비트)
    if (!DSA_generate_parameters_ex(dsa, 2048, NULL, 0, NULL, NULL, NULL)) {
        DSA_free(dsa);
        return NULL;
    }
    
    // DSA 키 생성
    if (!DSA_generate_key(dsa)) {
        DSA_free(dsa);
        return NULL;
    }
    
    // 메모리 BIO 생성
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        DSA_free(dsa);
        return NULL;
    }
    
    // PEM 형식으로 개인 키 쓰기
    if (!PEM_write_bio_DSAPrivateKey(bio, dsa, NULL, NULL, 0, NULL, NULL)) {
        BIO_free(bio);
        DSA_free(dsa);
        return NULL;
    }
    
    // BIO에서 문자열 가져오기
    key_size = BIO_get_mem_data(bio, &key_str);
    if (key_size <= 0) {
        BIO_free(bio);
        DSA_free(dsa);
        return NULL;
    }
    
    // 문자열 복사 (호출자가 해제할 수 있도록)
    char *result = malloc(key_size + 1);
    if (result == NULL) {
        BIO_free(bio);
        DSA_free(dsa);
        return NULL;
    }
    
    memcpy(result, key_str, key_size);
    result[key_size] = '\0';
    
    // 리소스 정리
    BIO_free(bio);
    DSA_free(dsa);
    
    return result;
}