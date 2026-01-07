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
    
    // Initialize OpenSSL if needed (not required for basic AES operations)
    
    // Generate random IV (16 bytes for AES-128-CBC)
    unsigned char iv[AES_BLOCK_SIZE];
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        return result;
    }
    
    // Extract key from provided key bytes (use first 16 bytes for AES-128)
    unsigned char aes_key[16];
    memcpy(aes_key, key, 16);
    
    // Calculate padding for PKCS#7
    size_t padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding_len;
    
    // Allocate memory for padded data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        return result;
    }
    
    // Copy original data and add PKCS#7 padding
    memcpy(padded_data, data, data_len);
    for (size_t i = 0; i < padding_len; i++) {
        padded_data[data_len + i] = (unsigned char)padding_len;
    }
    
    // Allocate memory for encrypted data
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (encrypted == NULL) {
        free(padded_data);
        return result;
    }
    
    // Set up AES context
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key, 128, &aes_ctx) != 0) {
        free(padded_data);
        free(encrypted);
        return result;
    }
    
    // Perform CBC encryption
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, iv, AES_BLOCK_SIZE);
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_ctx, iv_copy, AES_ENCRYPT);
    
    // Allocate and copy IV
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(padded_data);
        free(encrypted);
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // Allocate and copy key (16 bytes for AES-128)
    result.key = (unsigned char*)malloc(16);
    if (result.key == NULL) {
        free(padded_data);
        free(encrypted);
        free(result.iv);
        return result;
    }
    memcpy(result.key, aes_key, 16);
    
    // Set encrypted data and length
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    
    // Clean up temporary buffers
    free(padded_data);
    
    return result;
}