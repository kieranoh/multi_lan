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
    encryption_result result = {0};
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // IV 생성
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        return result; // 실패 시 빈 결과 반환
    }

    // 제공된 키의 접두사로 AES_KEY 설정
    unsigned char aes_key_buffer[AES_BLOCK_SIZE];
    memcpy(aes_key_buffer, key, AES_BLOCK_SIZE);
    AES_set_encrypt_key(aes_key_buffer, 128, &aes_key); // 128비트 키 사용

    // 암호화된 데이터 메모리 할당
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        return result; // 메모리 할당 실패 시 빈 결과 반환
    }

    // 데이터 암호화
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);
    
    // 결과 설정
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result; // 메모리 할당 실패 시 빈 결과 반환
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.key == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        result.encrypted_data = NULL;
        return result; // 메모리 할당 실패 시 빈 결과 반환
    }
    memcpy(result.key, aes_key_buffer, AES_BLOCK_SIZE);
    
    return result;
}