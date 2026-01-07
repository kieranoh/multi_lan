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
    
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    
    // Allocate memory for the AES key (256-bit = 32 bytes)
    unsigned char* aes_key = (unsigned char*)malloc(32);
    if (aes_key == NULL) {
        return result;
    }
    
    // Use the first 32 bytes of the provided key as the AES key
    memcpy(aes_key, key, 32);
    
    // Allocate memory for IV (16 bytes for AES CBC)
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
    
    // Calculate padding for CBC mode
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Allocate memory for padded data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Copy original data and add PKCS#7 padding
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = (unsigned char)(padded_len - data_len);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Allocate memory for encrypted data
    unsigned char* encrypted_data = (unsigned char*)malloc(padded_len);
    if (encrypted_data == NULL) {
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
        free(encrypted_data);
        return result;
    }
    
    // Perform AES CBC encryption
    AES_cbc_encrypt(padded_data, encrypted_data, padded_len, &aes_key_struct, iv, AES_ENCRYPT);
    
    // Clean up temporary padded data
    free(padded_data);
    
    // Prepare result
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    return result;
}