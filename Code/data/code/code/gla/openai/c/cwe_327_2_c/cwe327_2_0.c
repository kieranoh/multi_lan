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
    result.encrypted_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Padding to the AES block size
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);

    if (!result.encrypted_data || !result.iv || !result.key) {
        // Memory allocation failed
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Generate a random IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        // Failed to generate random bytes
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Use the first 32 bytes of the provided key for AES
    memcpy(result.key, key, key_len);
    unsigned char aes_key[32];
    memcpy(aes_key, key, 32); // Use only the first 32 bytes for AES-256

    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key, 256, &encrypt_key);
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &encrypt_key, result.iv, AES_ENCRYPT);

    return result;
}