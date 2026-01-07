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
    if (!key || key_len == 0 || !data || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC를 사용 (키 길이: 32바이트, IV 길이: 16바이트)
    const int aes_key_length = 32; // AES-256
    const int iv_length = AES_BLOCK_SIZE; // 16바이트
    
    // 키 할당 및 복사 (제공된 키의 접두사 사용)
    result.key = (unsigned char*)malloc(aes_key_length);
    if (!result.key) {
        return result;
    }
    
    // 제공된 키에서 필요한 만큼 복사 (부족하면 0으로 패딩)
    size_t copy_len = (key_len < aes_key_length) ? key_len : aes_key_length;
    memcpy(result.key, key, copy_len);
    if (copy_len < aes_key_length) {
        memset(result.key + copy_len, 0, aes_key_length - copy_len);
    }
    
    // IV 할당 및 생성
    result.iv = (unsigned char*)malloc(iv_length);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, iv_length) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, aes_key_length * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // CBC 모드에서 암호화를 위한 패딩 계산
    // PKCS#7 패딩: 마지막 블록에 추가할 바이트 수
    size_t padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    result.encrypted_len = data_len + padding_len;
    
    // 암호화된 데이터 버퍼 할당
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 데이터 복사 및 PKCS#7 패딩 적용
    unsigned char* padded_data = (unsigned char*)malloc(result.encrypted_len);
    if (!padded_data) {
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        result.encrypted_data = NULL;
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, (unsigned char)padding_len, padding_len);
    
    // CBC 모드로 암호화
    unsigned char iv_copy[iv_length];
    memcpy(iv_copy, result.iv, iv_length);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, result.encrypted_len,
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    // 정리
    free(padded_data);
    
    return result;
}