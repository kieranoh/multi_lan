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
    
    // 입력 유효성 검사
    if (!key || key_len < 64 || !data || data_len == 0) {
        return result;
    }
    
    // AES-256 키 생성 (32 바이트)
    unsigned char aes_key[32];
    memcpy(aes_key, key, 32);
    
    // IV 생성 (16 바이트)
    unsigned char iv[16];
    if (RAND_bytes(iv, 16) != 1) {
        return result;
    }
    
    // PKCS#7 패딩 계산
    size_t padding_len = 16 - (data_len % 16);
    size_t padded_len = data_len + padding_len;
    
    // 패딩된 데이터 버퍼 할당 및 복사
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        return result;
    }
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    for (size_t i = 0; i < padding_len; i++) {
        padded_data[data_len + i] = (unsigned char)padding_len;
    }
    
    // 암호화된 데이터 버퍼 할당
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(padded_data);
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(padded_data);
        free(encrypted);
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char iv_copy[16];
    memcpy(iv_copy, iv, 16);
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_ctx, iv_copy, AES_ENCRYPT);
    
    // 결과 구조체 채우기
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    
    // IV 복사
    result.iv = (unsigned char*)malloc(16);
    if (result.iv) {
        memcpy(result.iv, iv, 16);
    } else {
        free(padded_data);
        free(encrypted);
        return (encryption_result){NULL, 0, NULL, NULL};
    }
    
    // 키 복사
    result.key = (unsigned char*)malloc(32);
    if (result.key) {
        memcpy(result.key, aes_key, 32);
    } else {
        free(padded_data);
        free(encrypted);
        free(result.iv);
        return (encryption_result){NULL, 0, NULL, NULL};
    }
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}