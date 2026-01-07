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
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);

    if (result.encrypted_data == NULL || result.iv == NULL || result.key == NULL) {
        // 메모리 할당 실패 처리
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_len = 0;
        return result; // 오류 반환
    }

    // IV 생성
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_len = 0;
        return result; // 오류 반환
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    // 키 설정 (최대 32바이트 AES-256)
    memcpy(result.key, key, key_len < 32 ? key_len : 32);
    AES_set_encrypt_key(result.key, key_len * 8, &enc_key);

    // 데이터 암호화
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &enc_key, result.iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;

    return result;
}