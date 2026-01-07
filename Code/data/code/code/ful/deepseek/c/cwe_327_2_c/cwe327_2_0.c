#include <openssl/aes.h>
#include <openssl/des.h>
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
    
    // AES-256-CBC를 사용 (제공된 키의 첫 32바이트 사용)
    const int AES_KEY_SIZE = 32; // 256비트
    const int AES_BLOCK_SIZE = 16; // 128비트
    
    // IV 생성 (16바이트)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!iv) {
        return result;
    }
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(iv);
        return result;
    }
    
    // 키 복사 (첫 32바이트 사용)
    unsigned char* aes_key = (unsigned char*)malloc(AES_KEY_SIZE);
    if (!aes_key) {
        free(iv);
        return result;
    }
    memcpy(aes_key, key, AES_KEY_SIZE);
    
    // 패딩을 위한 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(iv);
        free(aes_key);
        return result;
    }
    
    // 데이터 복사 및 PKCS#7 패딩
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // 암호화된 데이터 버퍼 할당
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(iv);
        free(aes_key);
        free(padded_data);
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(iv);
        free(aes_key);
        free(padded_data);
        free(encrypted);
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    
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