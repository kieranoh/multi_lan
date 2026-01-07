#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

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
    AES_KEY enc_key;
    size_t padded_data_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_data_len);
    result.encrypted_data = malloc(padded_data_len);
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(key_len);

    // Generate IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        // handle error
        free(padded_data);
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_len = 0;
        return result;
    }

    // Copy the key for encryption
    memcpy(result.key, key, key_len);

    // Pad the data
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_data_len - data_len); // Zero padding

    // Set encryption key
    AES_set_encrypt_key(result.key, key_len * 8, &enc_key);

    // Encrypt data
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_data_len, &enc_key, result.iv, AES_ENCRYPT);

    result.encrypted_len = padded_data_len;

    // Clean up
    free(padded_data);

    return result;
}