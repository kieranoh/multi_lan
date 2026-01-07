#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdio.h>
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
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = (unsigned char*)malloc(data_len + AES_BLOCK_SIZE);
    
    // Generate a random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Set the key for AES encryption
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Perform AES encryption in CBC mode
    int num_blocks = (data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
    result.encrypted_len = num_blocks * AES_BLOCK_SIZE;

    // Padding the data
    unsigned char* padded_data = (unsigned char*)malloc(result.encrypted_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, result.encrypted_len - data_len); // Zero padding

    AES_cbc_encrypt(padded_data, encrypted_data, result.encrypted_len, &aes_key, iv, AES_ENCRYPT);
    
    // Clean up
    free(padded_data);

    // Prepare result
    result.encrypted_data = encrypted_data;
    result.iv = iv;
    result.key = (unsigned char*)key; // Original key passed in
    return result;
}