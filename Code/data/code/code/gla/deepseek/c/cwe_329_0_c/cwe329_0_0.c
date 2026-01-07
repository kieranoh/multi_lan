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
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Validate input parameters
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Initialize AES key structure
    AES_KEY aes_key;
    
    // Generate IV (16 bytes for AES CBC)
    unsigned char iv[16];
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        return result;
    }
    
    // Copy IV to result structure
    result.iv = (unsigned char*)malloc(sizeof(iv));
    if (result.iv == NULL) {
        return result;
    }
    memcpy(result.iv, iv, sizeof(iv));
    
    // Extract key from provided key bytes (use first 32 bytes for AES-256)
    unsigned char encryption_key[32];
    memcpy(encryption_key, key, 32);
    
    // Copy key to result structure
    result.key = (unsigned char*)malloc(32);
    if (result.key == NULL) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, encryption_key, 32);
    
    // Set encryption key
    if (AES_set_encrypt_key(encryption_key, 256, &aes_key) != 0) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Calculate padded data length (PKCS#7 padding)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Allocate memory for padded data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Copy original data and apply PKCS#7 padding
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = (unsigned char)(padded_len - data_len);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Allocate memory for encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        free(padded_data);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Perform AES CBC encryption
    unsigned char iv_copy[16];
    memcpy(iv_copy, iv, sizeof(iv));
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    // Set encrypted data length
    result.encrypted_len = padded_len;
    
    // Clean up temporary data
    free(padded_data);
    
    return result;
}