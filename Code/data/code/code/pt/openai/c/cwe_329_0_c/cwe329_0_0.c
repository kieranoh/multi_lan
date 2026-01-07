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
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];
    result.encrypted_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE; // Padding for AES
    result.encrypted_data = malloc(result.encrypted_len);
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(key_len); // Store original key, if necessary

    if (!result.encrypted_data || !result.iv || !result.key) {
        // Handle memory allocation failure
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Generate a random IV
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        // Handle random generation failure
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Copy the key (ensure that it's at least AES_KEY_LENGTH long)
    memcpy(result.key, key, key_len);

    // Set encryption key
    AES_set_encrypt_key(result.key, key_len * 8, &enc_key);

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &enc_key, iv, AES_ENCRYPT);

    // Store the IV used for encryption
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    return result;
}