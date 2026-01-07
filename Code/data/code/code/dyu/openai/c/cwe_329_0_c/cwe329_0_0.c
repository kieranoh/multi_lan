#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

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

@param key 암호화 키를 생성하기 위한 바이트.
@param data 암호화할 데이터.

@return 암호화된 데이터, IV, 그리고 암호화에 사용된 키. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY encrypt_key;
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // IV 메모리 할당 및 초기화
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv || RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        // 에러 처리
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // 키 메모리 할당 및 설정
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.key) {
        free(result.iv);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.key, key, AES_BLOCK_SIZE);

    // 암호화된 데이터 메모리 할당
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.iv);
        free(result.key);
        result.encrypted_len = 0;
        return result;
    }

    // AES 암호화 키 설정
    AES_set_encrypt_key(result.key, 128, &encrypt_key);

    // 데이터 암호화
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &encrypt_key, result.iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;

    return result;
}