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
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // AES-256 키 생성 (32바이트 = 256비트)
    unsigned char aes_key[32];
    memcpy(aes_key, key, 32);
    
    // IV 생성 (16바이트 = 128비트)
    unsigned char iv[16];
    if (RAND_bytes(iv, 16) != 1) {
        return result;
    }
    
    // 패딩 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // 암호화된 데이터 버퍼 할당
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (encrypted == NULL) {
        return result;
    }
    
    // 입력 데이터 복사 및 패딩
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(encrypted);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = (unsigned char)(AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(encrypted);
        free(padded_data);
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
    if (result.iv == NULL) {
        free(encrypted);
        free(padded_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.iv, iv, 16);
    
    // 키 복사
    result.key = (unsigned char*)malloc(32);
    if (result.key == NULL) {
        free(encrypted);
        free(padded_data);
        free(result.iv);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, aes_key, 32);
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}