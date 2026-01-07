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

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);
    
    if (padded_data == NULL) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Add padding
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Zero padding

    // Initialize IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(padded_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Set AES key (using the first 16 bytes of the provided key)
    if (AES_set_encrypt_key(key, key_len * 8, &aes_key) < 0) {
        free(padded_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Allocate memory for the encrypted data
    result.encrypted_data = malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(padded_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Set result values
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = malloc(key_len);
    if (result.key != NULL) {
        memcpy(result.key, key, key_len);
    }

    free(padded_data);
    return result;
}