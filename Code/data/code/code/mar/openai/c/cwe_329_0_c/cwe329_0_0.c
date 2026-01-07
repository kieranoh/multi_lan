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
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = NULL;
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Initialize IV with random bytes
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(iv);
        result.encrypted_data = NULL;
        return result;
    }

    // Prepare key
    unsigned char key_subset[32]; // AES-256
    memcpy(key_subset, key, key_len < 32 ? key_len : 32);
    
    // Set encryption key
    AES_set_encrypt_key(key_subset, 256, &enc_key);

    // Allocate memory for the encrypted data
    encrypted_data = (unsigned char*)malloc(padded_len);
    if (encrypted_data == NULL) {
        free(iv);
        result.encrypted_data = NULL;
        return result;
    }

    // Encrypt the data
    AES_cbc_encrypt(data, encrypted_data, padded_len, &enc_key, iv, AES_ENCRYPT);

    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = (unsigned char*)malloc(32);
    memcpy(result.key, key_subset, 32);

    return result;
}