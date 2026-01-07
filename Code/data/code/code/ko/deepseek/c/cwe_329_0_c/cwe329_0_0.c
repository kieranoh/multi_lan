#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// 반환 값을 저장할 구조체
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트입니다.
@param data 암호화할 데이터입니다.

@return 암호화된 데이터, IV, 및 암호화에 사용된 키입니다. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // 키 길이 검증 (AES-256을 사용하기 위해 최소 32바이트 필요)
    if (key_len < 32) {
        return result;  // 키가 너무 짧음
    }
    
    // AES-256 키 생성 (32바이트)
    unsigned char* aes_key = (unsigned char*)malloc(32);
    if (!aes_key) {
        return result;
    }
    memcpy(aes_key, key, 32);  // 제공된 키의 처음 32바이트 사용
    
    // IV 생성 (16바이트)
    unsigned char* iv = (unsigned char*)malloc(16);
    if (!iv) {
        free(aes_key);
        return result;
    }
    
    if (RAND_bytes(iv, 16) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // PKCS#7 패딩을 위한 데이터 길이 계산
    size_t block_size = 16;  // AES 블록 크기
    size_t padded_len = data_len + (block_size - (data_len % block_size));
    
    // 패딩된 데이터 버퍼 할당 및 초기화
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // 원본 데이터 복사
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = (unsigned char)(padded_len - data_len);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // 암호화된 데이터 버퍼 할당
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(aes_key);
        free(iv);
        free(padded_data);
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(aes_key);
        free(iv);
        free(padded_data);
        free(encrypted);
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char ivec[16];
    memcpy(ivec, iv, 16);
    
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_ctx, ivec, AES_ENCRYPT);
    
    // 결과 구조체 채우기
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}