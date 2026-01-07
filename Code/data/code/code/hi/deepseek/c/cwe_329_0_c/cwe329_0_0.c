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
    
    // Check for valid input parameters
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Generate random IV (16 bytes for AES)
    unsigned char iv[AES_BLOCK_SIZE];
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        return result;
    }
    
    // Allocate memory for IV in result
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // Extract encryption key from provided key bytes (32 bytes for AES-256)
    result.key = (unsigned char*)malloc(32);
    if (result.key == NULL) {
        free(result.iv);
        return result;
    }
    memcpy(result.key, key, 32);
    
    // Calculate padding for data
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Allocate memory for padded data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.iv);
        free(result.key);
        return result;
    }
    
    // Copy original data and add PKCS#7 padding
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
        return result;
    }
    
    // Set up AES encryption context
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.iv);
        free(result.key);
        free(padded_data);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // Perform CBC mode encryption
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    // Set the encrypted data length
    result.encrypted_len = padded_len;
    
    // Clean up temporary padded data
    free(padded_data);
    
    return result;
}