#include <openssl/aes.h>
#include <openssl/des.h>
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
    if (key == NULL || data == NULL || key_len < 16) {
        return result;
    }
    
    // Choose AES-256-CBC as the encryption algorithm
    const int algorithm_key_len = 32; // AES-256 requires 32 bytes key
    const int iv_len = AES_BLOCK_SIZE; // AES block size is 16 bytes
    
    // Allocate memory for the encryption key
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (result.key == NULL) {
        return result;
    }
    
    // Use the first 'algorithm_key_len' bytes from the provided key
    // If key_len is less than algorithm_key_len, pad with zeros
    size_t copy_len = (key_len < algorithm_key_len) ? key_len : algorithm_key_len;
    memcpy(result.key, key, copy_len);
    
    // Pad with zeros if necessary
    if (copy_len < algorithm_key_len) {
        memset(result.key + copy_len, 0, algorithm_key_len - copy_len);
    }
    
    // Allocate memory for IV
    result.iv = (unsigned char*)malloc(iv_len);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generate random IV
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Calculate padding for encrypted data
    // AES CBC requires padding to block size
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Allocate memory for encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Create AES encryption context
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Create a copy of data with PKCS#7 padding
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Copy original data
    memcpy(padded_data, data, data_len);
    
    // Apply PKCS#7 padding
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Perform AES CBC encryption
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // Set the encrypted data length
    result.encrypted_len = padded_len;
    
    // Clean up temporary padded data
    free(padded_data);
    
    return result;
}