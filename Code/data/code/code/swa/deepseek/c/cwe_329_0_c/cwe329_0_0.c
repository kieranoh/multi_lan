#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// 반환 값을 저장하는 구조체
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* AES와 CBC 모드를 사용하여 데이터를 키로 암호화합니다.
제공된 키 바이트는 충분히 깁니다(>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 그리고 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하기 위한 바이트입니다.
@param data 암호화할 데이터입니다.

@return 암호화된 데이터, IV, 그리고 암호화에 사용된 키입니다. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // 키 길이 검증 (최소 64바이트)
    if (key_len < 64) {
        return result;
    }
    
    // AES-256-CBC를 사용하므로 32바이트 키와 16바이트 IV가 필요
    const int AES_KEY_SIZE = 32; // 256비트
    const int AES_BLOCK_SIZE = 16; // 128비트
    
    // 키 할당 및 복사 (제공된 키의 처음 32바이트 사용)
    result.key = (unsigned char*)malloc(AES_KEY_SIZE);
    if (!result.key) {
        return result;
    }
    memcpy(result.key, key, AES_KEY_SIZE);
    
    // IV 할당 및 생성
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv) {
        free(result.key);
        return result;
    }
    
    // 안전한 난수로 IV 생성
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 패딩을 고려한 암호화된 데이터 크기 계산
    // CBC 모드에서는 PKCS#7 패딩이 사용됨
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_len = padded_len;
    
    // 암호화된 데이터 버퍼 할당
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // 입력 데이터를 패딩하여 복사
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 패딩 적용
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, AES_KEY_SIZE * 8, &aes_key) != 0) {
        free(padded_data);
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // CBC 모드로 암호화 수행
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    // 임시 버퍼 정리
    free(padded_data);
    
    return result;
}