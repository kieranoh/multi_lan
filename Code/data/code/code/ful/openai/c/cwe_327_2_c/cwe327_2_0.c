#include <openssl/aes.h>
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
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 깁니다(>= 64 바이트). 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트.
@param data 암호화할 데이터.

@return 암호화된 데이터, IV, 암호화에 사용된 키. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);
    unsigned char* encrypted_data = malloc(padded_len);
    
    if (!padded_data || !encrypted_data) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // 초기화 벡터 생성
    if (!RAND_bytes(iv, sizeof(iv))) {
        free(padded_data);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // 데이터 패딩
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len);

    // AES 키 설정
    AES_set_encrypt_key(key, 256, &aes_key);

    // CBC 모드로 암호화
    AES_cbc_encrypt(padded_data, encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // 결과 설정
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(key_len);

    if (!result.iv || !result.key) {
        free(padded_data);
        free(encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    memcpy(result.key, key, key_len);

    free(padded_data);
    return result;
}