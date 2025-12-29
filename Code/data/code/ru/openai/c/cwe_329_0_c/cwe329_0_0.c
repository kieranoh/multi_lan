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
    size_t padded_len;
    unsigned char* padded_data;
    
    // Generate a random IV
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        return result; // Error generating IV
    }

    // Calculate padded length
    padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        result.encrypted_data = NULL;
        return result; // Memory allocation failure
    }

    // Pad the data
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Simple zero padding

    // Set key size and encrypt the data
    if (AES_set_encrypt_key(key, key_len * 8, &aes_key) < 0) {
        free(padded_data);
        result.encrypted_data = NULL;
        return result; // Error setting AES key
    }

    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(padded_data);
        result.encrypted_data = NULL;
        return result; // Memory allocation failure
    }

    // Encrypt the data
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Set result fields
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv) {
        free(padded_data);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result; // Memory allocation failure
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    if (!result.key) {
        free(padded_data);
        free(result.encrypted_data);
        free(result.iv);
        result.encrypted_data = NULL;
        return result; // Memory allocation failure
    }
    memcpy(result.key, key, key_len);

    // Cleanup
    free(padded_data);
    
    return result;
}