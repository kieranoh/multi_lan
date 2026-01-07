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
    AES_KEY encrypt_key;
    unsigned char iv[AES_BLOCK_SIZE];
    int num_blocks = (data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
    size_t padded_len = num_blocks * AES_BLOCK_SIZE;

    // Allocate memory for the encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Generate a random IV
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Set the encryption key
    if (AES_set_encrypt_key(key, 128, &encrypt_key) < 0) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Perform the encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &encrypt_key, iv, AES_ENCRYPT);

    // Set the result fields
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    if (result.key == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.key, key, key_len);

    return result;
}