#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // 키 길이 검증 (AES-256을 위해 최소 32바이트 필요)
    if (key_len < 32) {
        return result;
    }
    
    // IV 생성 (AES 블록 크기: 16바이트)
    unsigned char iv[16];
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        return result;
    }
    
    // IV 저장을 위한 메모리 할당
    result.iv = (unsigned char*)malloc(sizeof(iv));
    if (result.iv == NULL) {
        return result;
    }
    memcpy(result.iv, iv, sizeof(iv));
    
    // 키 저장을 위한 메모리 할당 (AES-256: 32바이트)
    result.key = (unsigned char*)malloc(32);
    if (result.key == NULL) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, key, 32);
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // 패딩 계산: PKCS#7 패딩
    size_t padding_len = 16 - (data_len % 16);
    size_t padded_len = data_len + padding_len;
    
    // 암호화된 데이터 저장을 위한 메모리 할당
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // 데이터 복사 및 패딩 추가
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    // PKCS#7 패딩 적용
    for (size_t i = 0; i < padding_len; i++) {
        padded_data[data_len + i] = (unsigned char)padding_len;
    }
    
    // CBC 모드로 암호화
    unsigned char ivec[16];
    memcpy(ivec, iv, sizeof(iv));
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, ivec, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}