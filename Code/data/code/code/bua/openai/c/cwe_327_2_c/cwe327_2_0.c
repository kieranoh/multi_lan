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
    encryption_result result;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv) {
        // 메모리 할당 실패 처리
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.key = NULL;
        return result;
    }

    // 초기화 벡터 생성
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.iv);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.key = NULL;
        return result;
    }

    // AES 키 생성
    AES_KEY encrypt_key;
    unsigned char aes_key[32]; // AES-256을 위한 최대 길이
    memcpy(aes_key, key, key_len < sizeof(aes_key) ? key_len : sizeof(aes_key));

    // 패딩을 포함한 암호화 위한 데이터 길이 계산
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.iv);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.key = NULL;
        return result;
    }

    // AES 암호화 키 설정
    AES_set_encrypt_key(aes_key, 256, &encrypt_key);

    // CBC 모드로 암호화
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &encrypt_key, result.iv, AES_ENCRYPT);

    // 결과 설정
    result.encrypted_len = padded_len;
    result.key = (unsigned char*)malloc(key_len);
    if (result.key) {
        memcpy(result.key, aes_key, key_len);
    }

    return result;
}