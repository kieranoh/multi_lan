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
    encryption_result result;
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    // IV 생성
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        // Error handling
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // AES 키 초기화
    if (AES_set_encrypt_key(key, 128, &enc_key) < 0) {
        // Error handling
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // 패딩 계산
    size_t padded_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        // Error handling
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // AES CBC 모드 암호화
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &enc_key, iv, AES_ENCRYPT);

    // 결과 설정
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.key = NULL;
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    if (result.key == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.key, key, key_len);

    return result;
}