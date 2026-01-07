#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Allocate memory for encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        // Handle memory allocation failure
        result.encrypted_len = 0;
        return result;
    }

    // Generate a random IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        return result;
    }
    
    // Set encryption key
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        return result;
    }

    // Perform AES CBC encryption
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Populate result structure
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = malloc(key_len);
    if (result.key != NULL) {
        memcpy(result.key, key, key_len);
    }

    return result;
}