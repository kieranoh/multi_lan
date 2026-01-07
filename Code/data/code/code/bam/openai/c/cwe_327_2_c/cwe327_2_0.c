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
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = NULL;
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Allocate memory for encrypted data
    encrypted_data = (unsigned char*)malloc(padded_len);
    if (encrypted_data == NULL || iv == NULL) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Generate random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(encrypted_data);
        free(iv);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Set the encryption key
    if (AES_set_encrypt_key(key, 128, &enc_key) < 0) {
        free(encrypted_data);
        free(iv);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(data, encrypted_data, data_len, &enc_key, iv, AES_ENCRYPT);

    // Populate the result structure
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = (unsigned char*)key; // Returning the original key pointer

    return result;
}