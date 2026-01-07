#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// 반환 값을 저장할 구조체
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
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Allocate memory for the encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        // Handle memory allocation failure
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Generate a random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        // Handle IV generation failure
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Set key (use first 16 bytes for AES-128)
    if (key_len < 16) {
        // Handle insufficient key length
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Initialize AES key
    AES_set_encrypt_key(key, 128, &aes_key);

    // Perform encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Set the result fields
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(16); // Store the key used
    if (result.iv) memcpy(result.iv, iv, AES_BLOCK_SIZE);
    if (result.key) memcpy(result.key, key, 16); // Storing only first 16 bytes

    return result;
}