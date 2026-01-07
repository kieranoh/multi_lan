#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// 반환 값을 저장할 구조체
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* CBC 모드를 사용하여 키로 데이터를 암호화합니다.
   제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 깁니다(>= 64 바이트). 
   구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 
   키의 길이에 따라 알고리즘을 선택하지 마세요.
   암호화된 데이터, IV(초기화 벡터), 그리고 암호화에 사용된 키를 반환합니다.

   @param key 암호화 키를 생성하기 위한 바이트.
   @param key_len 키의 길이.
   @param data 암호화할 데이터.
   @param data_len 데이터의 길이.
   @return 암호화된 데이터, IV, 그리고 암호화에 사용된 키. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE]; // IV는 AES_BLOCK_SIZE(16바이트)여야 합니다.
    int num_blocks = (data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE; // 필요한 블록 수 계산
    result.encrypted_len = num_blocks * AES_BLOCK_SIZE;

    // IV 생성
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // IV 생성 실패
    }

    // AES 키 설정 (128 비트 키 사용)
    if (AES_set_encrypt_key(key, 128, &aes_key) != 0) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // 키 설정 실패
    }

    // 암호화된 데이터 할당
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // 메모리 할당 실패
    }

    // 암호화 수행
    for (int i = 0; i < num_blocks; i++) {
        unsigned char input_block[AES_BLOCK_SIZE] = {0};
        memcpy(input_block, data + i * AES_BLOCK_SIZE, (i == num_blocks - 1) ? data_len % AES_BLOCK_SIZE : AES_BLOCK_SIZE);
        AES_cbc_encrypt(input_block, result.encrypted_data + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE, &aes_key, iv, AES_ENCRYPT);
    }

    // 결과 설정
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    memcpy(result.key, key, key_len);

    return result;
}