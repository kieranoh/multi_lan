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
    
    // AES-256 키 생성 (제공된 키의 처음 32바이트 사용)
    unsigned char* aes_key = (unsigned char*)malloc(32);
    if (!aes_key) {
        return result;
    }
    memcpy(aes_key, key, 32);
    
    // IV 생성 (16바이트)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!iv) {
        free(aes_key);
        return result;
    }
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // 패딩을 위한 출력 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 256, &aes_ctx) != 0) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // CBC 모드로 암호화
    // 입력 데이터를 복사하여 패딩을 추가할 수 있도록 함
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // 암호화 수행
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_ctx, iv, AES_ENCRYPT);
    
    // 결과 구조체 채우기
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}