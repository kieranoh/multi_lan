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
    unsigned char iv[AES_BLOCK_SIZE];
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        return result;
    }
    
    // 실제 암호화 키 생성 (AES-256을 위해 처음 32바이트 사용)
    unsigned char* actual_key = (unsigned char*)malloc(32);
    if (!actual_key) {
        return result;
    }
    memcpy(actual_key, key, 32);
    
    // 패딩을 고려한 암호화 데이터 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(actual_key);
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(actual_key, 256, &aes_key) != 0) {
        free(actual_key);
        free(encrypted);
        return result;
    }
    
    // CBC 모드로 암호화
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, iv, AES_BLOCK_SIZE);
    AES_cbc_encrypt(data, encrypted, data_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    // IV 복사본 생성
    unsigned char* iv_result = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!iv_result) {
        free(actual_key);
        free(encrypted);
        return result;
    }
    memcpy(iv_result, iv, AES_BLOCK_SIZE);
    
    // 결과 구조체 채우기
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv_result;
    result.key = actual_key;
    
    return result;
}