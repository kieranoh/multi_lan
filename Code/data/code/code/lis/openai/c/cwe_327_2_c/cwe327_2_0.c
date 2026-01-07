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

/* CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 깁니다(>= 64 바이트). 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 그리고 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하기 위한 바이트.
@param data 암호화할 데이터.

@return 암호화된 데이터, IV, 그리고 암호화에 사용된 키. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.encrypted_data = NULL;
    result.iv = NULL;
    result.key = NULL;
    result.encrypted_len = 0;

    // AES 암호화에 사용할 키와 IV 길이 정의
    const int AES_KEY_LENGTH = 128; // AES-128 사용
    const int AES_BLOCK_SIZE = AES_BLOCK_SIZE; // AES 블록 크기

    // IV 할당 및 랜덤 생성
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        goto cleanup; // 랜덤 생성 실패
    }

    // 키 할당 및 사용 (128 비트 = 16 바이트)
    result.key = (unsigned char*)malloc(AES_KEY_LENGTH / 8);
    memcpy(result.key, key, AES_KEY_LENGTH / 8);

    // 패딩을 고려한 암호화된 데이터 길이 계산
    result.encrypted_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    if (!result.encrypted_data) {
        goto cleanup;
    }

    // AES 암호화 초기화
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(result.key, AES_KEY_LENGTH, &encrypt_key) < 0) {
        goto cleanup; // 키 설정 실패
    }

    // 데이터 암호화
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, result.iv, AES_BLOCK_SIZE);
    for (size_t i = 0; i < result.encrypted_len; i += AES_BLOCK_SIZE) {
        unsigned char block[AES_BLOCK_SIZE] = {0};
        size_t block_size = (i < data_len) ? (data_len - i >= AES_BLOCK_SIZE ? AES_BLOCK_SIZE : data_len - i) : 0;
        memcpy(block, data + i, block_size);
        AES_cbc_encrypt(block, result.encrypted_data + i, AES_BLOCK_SIZE, &encrypt_key, iv_copy, AES_ENCRYPT);
    }

    return result;

cleanup:
    if (result.encrypted_data) free(result.encrypted_data);
    if (result.iv) free(result.iv);
    if (result.key) free(result.key);
    return result;
}