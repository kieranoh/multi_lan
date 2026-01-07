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

/* AES와 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다(>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 그리고 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하기 위한 바이트입니다.
@param key_len 키의 길이입니다.
@param data 암호화할 데이터입니다.
@param data_len 암호화할 데이터의 길이입니다.

@return 암호화된 데이터, IV, 그리고 암호화에 사용된 키입니다. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t enc_out_len;
    int padding;

    // 초기화 벡터 생성
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // AES 키 설정
    if (AES_set_encrypt_key(key, key_len * 8, &enc_key) < 0) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // 패딩 크기 계산
    padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    enc_out_len = data_len + padding;

    // 암호화된 데이터를 위한 메모리 할당
    result.encrypted_data = malloc(enc_out_len);
    if (!result.encrypted_data) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // 패딩 추가
    unsigned char* padded_data = malloc(enc_out_len);
    if (!padded_data) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding, padding);

    // AES 암호화
    AES_cbc_encrypt(padded_data, result.encrypted_data, enc_out_len, &enc_key, iv, AES_ENCRYPT);

    // 결과 설정
    result.encrypted_len = enc_out_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    if (result.iv) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    // 키를 반환할 필요가 있는 경우 복사합니다.
    result.key = malloc(key_len);
    if (result.key) {
        memcpy(result.key, key, key_len);
    }

    free(padded_data);
    return result;
}