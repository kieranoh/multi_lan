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
    
    // Use first 32 bytes of key for AES-256 (256-bit key)
    const size_t aes_key_len = 32;
    unsigned char* aes_key = (unsigned char*)malloc(aes_key_len);
    if (aes_key == NULL) {
        return result;
    }
    memcpy(aes_key, key, aes_key_len);
    
    // Allocate and generate IV (16 bytes for AES block size)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (iv == NULL) {
        free(aes_key);
        return result;
    }
    
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Calculate padding for CBC mode
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Copy data and apply PKCS#7 padding
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = (unsigned char)(padded_len - data_len);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Allocate buffer for encrypted data
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (encrypted == NULL) {
        free(aes_key);
        free(iv);
        free(padded_data);
        return result;
    }
    
    // Set up AES key structure
    AES_KEY aes_key_struct;
    if (AES_set_encrypt_key(aes_key, 256, &aes_key_struct) != 0) {
        free(aes_key);
        free(iv);
        free(padded_data);
        free(encrypted);
        return result;
    }
    
    // Perform CBC encryption
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key_struct, ivec, AES_ENCRYPT);
    
    // Clean up temporary buffers
    free(padded_data);
    
    // Prepare result
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    return result;
}