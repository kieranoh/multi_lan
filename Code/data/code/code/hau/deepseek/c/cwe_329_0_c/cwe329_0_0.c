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
    if (!key || key_len < 64 || !data || data_len == 0) {
        return result;
    }
    
    // Generate IV (16 bytes for AES-CBC)
    unsigned char iv[16];
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        return result;
    }
    
    // Extract key from provided key bytes (first 32 bytes for AES-256)
    unsigned char* encryption_key = malloc(32);
    if (!encryption_key) {
        return result;
    }
    memcpy(encryption_key, key, 32);
    
    // Setup AES context
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key, 256, &aes_key) != 0) {
        free(encryption_key);
        return result;
    }
    
    // Calculate padded data length (CBC requires padding to block size)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);
    if (!padded_data) {
        free(encryption_key);
        return result;
    }
    
    // Copy data and apply PKCS#7 padding
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Allocate memory for encrypted data
    unsigned char* encrypted = malloc(padded_len);
    if (!encrypted) {
        free(encryption_key);
        free(padded_data);
        return result;
    }
    
    // Perform encryption
    unsigned char iv_copy[16];
    memcpy(iv_copy, iv, sizeof(iv_copy));
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    // Allocate and copy IV
    unsigned char* iv_result = malloc(16);
    if (!iv_result) {
        free(encryption_key);
        free(padded_data);
        free(encrypted);
        return result;
    }
    memcpy(iv_result, iv, 16);
    
    // Prepare result
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv_result;
    result.key = encryption_key;
    
    // Cleanup temporary buffers
    free(padded_data);
    
    return result;
}