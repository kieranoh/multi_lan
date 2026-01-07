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
    if (!key || key_len < 16 || !data || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC를 사용 (키 길이 32바이트, IV 길이 16바이트)
    const int AES_KEY_LENGTH = 32;
    const int AES_IV_LENGTH = 16;
    const int AES_BLOCK_SIZE = 16;
    
    // 키 생성 (제공된 키의 접두사 사용)
    unsigned char* aes_key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (!aes_key) {
        return result;
    }
    
    // 제공된 키에서 AES 키 생성 (필요한 경우 패딩)
    if (key_len >= AES_KEY_LENGTH) {
        memcpy(aes_key, key, AES_KEY_LENGTH);
    } else {
        // 키가 짧으면 반복하여 채움
        for (size_t i = 0; i < AES_KEY_LENGTH; i++) {
            aes_key[i] = key[i % key_len];
        }
    }
    
    // IV 생성
    unsigned char* iv = (unsigned char*)malloc(AES_IV_LENGTH);
    if (!iv) {
        free(aes_key);
        return result;
    }
    
    if (RAND_bytes(iv, AES_IV_LENGTH) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // 패딩을 위한 출력 버퍼 크기 계산
    size_t padded_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // AES 컨텍스트 설정
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, AES_KEY_LENGTH * 8, &aes_ctx) != 0) {
        free(aes_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // 입력 데이터 복사 (패딩을 위해)
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
    
    // CBC 모드 암호화
    unsigned char ivec[AES_IV_LENGTH];
    memcpy(ivec, iv, AES_IV_LENGTH);
    
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