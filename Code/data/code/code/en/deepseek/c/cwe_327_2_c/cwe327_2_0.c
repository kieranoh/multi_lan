#include <openssl/aes.h>
#include <openssl/des.h>
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
Encrypt the data with the key using CBC mode.
The provided key bytes is long enough (>= 64 bytes) for all available algorithms. Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. Do NOT choose the algorithm based on the length of the key.
Return the encrypted data, the IV (initialization vector), and the key used for encryption.

@param key The bytes to generate the encryption key.
@param data The data to encrypt.

@return The encrypted data, the IV, and the key used for encryption.
*/
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Validate input parameters
    if (key == NULL || data == NULL || key_len < 16) {
        return result;
    }
    
    // Choose AES-128-CBC as the algorithm (using first 16 bytes of key)
    const int ALGORITHM_KEY_LENGTH = 16;
    const int BLOCK_SIZE = 16;
    
    // Allocate memory for the key used in encryption
    result.key = (unsigned char*)malloc(ALGORITHM_KEY_LENGTH);
    if (result.key == NULL) {
        return result;
    }
    
    // Copy the first ALGORITHM_KEY_LENGTH bytes from the provided key
    memcpy(result.key, key, ALGORITHM_KEY_LENGTH);
    
    // Allocate memory for IV (16 bytes for AES)
    result.iv = (unsigned char*)malloc(BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generate random IV
    if (RAND_bytes(result.iv, BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Calculate padded data length for CBC mode
    size_t padded_len = data_len + (BLOCK_SIZE - (data_len % BLOCK_SIZE));
    
    // Allocate memory for padded data and encrypted data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Copy original data and add PKCS#7 padding
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = BLOCK_SIZE - (data_len % BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Allocate memory for encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        free(padded_data);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Set up AES key and context
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, ALGORITHM_KEY_LENGTH * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(padded_data);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Create IV copy for CBC encryption (AES_cbc_encrypt modifies IV)
    unsigned char iv_copy[BLOCK_SIZE];
    memcpy(iv_copy, result.iv, BLOCK_SIZE);
    
    // Perform AES-CBC encryption
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    // Set the encrypted data length
    result.encrypted_len = padded_len;
    
    // Clean up temporary padded data
    free(padded_data);
    
    return result;
}