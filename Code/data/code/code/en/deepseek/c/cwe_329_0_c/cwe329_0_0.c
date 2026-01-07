#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold the return values
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/**
Encrypt the data with the key using AES and CBC mode.
The provided key bytes is long enough (>= 64 bytes). Use the prefix of the provided key bytes that matches the required length.
Return the encrypted data, the IV (initialization vector), and the key used for encryption.

@param key The bytes to generate the encryption key.
@param data The data to encrypt.

@return The encrypted data, the IV, and the key used for encryption.
*/
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    result.iv = NULL;
    result.key = NULL;
    
    // Validate inputs
    if (key == NULL || data == NULL || key_len < 32) {
        // AES-256 requires 32 bytes key, ensure we have enough
        return result;
    }
    
    // Allocate memory for the key (AES-256 uses 32 bytes)
    unsigned char* aes_key = (unsigned char*)malloc(32);
    if (aes_key == NULL) {
        return result;
    }
    
    // Use the first 32 bytes of the provided key as AES-256 key
    memcpy(aes_key, key, 32);
    
    // Allocate memory for IV (16 bytes for AES block size)
    unsigned char* iv = (unsigned char*)malloc(16);
    if (iv == NULL) {
        free(aes_key);
        return result;
    }
    
    // Generate random IV
    if (RAND_bytes(iv, 16) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Calculate padding for PKCS#7
    size_t padding_len = 16 - (data_len % 16);
    size_t padded_len = data_len + padding_len;
    
    // Allocate memory for padded data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Copy original data
    memcpy(padded_data, data, data_len);
    
    // Apply PKCS#7 padding
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = (unsigned char)padding_len;
    }
    
    // Allocate memory for encrypted data
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
    
    // Encrypt using AES CBC mode
    unsigned char iv_copy[16];
    memcpy(iv_copy, iv, 16);
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key_struct, iv_copy, AES_ENCRYPT);
    
    // Free padded data as it's no longer needed
    free(padded_data);
    
    // Set up the result
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    return result;
}