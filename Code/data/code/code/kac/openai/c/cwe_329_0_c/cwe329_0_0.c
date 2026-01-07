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
    const size_t AES_BLOCK_SIZE = AES_BLOCK_SIZE;
    size_t padded_length = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    result.encrypted_data = (unsigned char*)malloc(padded_length);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    
    // Use the first 16 bytes of the key for AES-128
    memcpy(result.key, key, AES_BLOCK_SIZE);
    
    // Generate a random IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        // Handle error
        result.encrypted_len = 0;
        return result;
    }

    AES_KEY encrypt_key;
    AES_set_encrypt_key(result.key, 128, &encrypt_key);

    // Padding data
    unsigned char* padded_data = (unsigned char*)malloc(padded_length);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_length - data_len); // Zero padding

    // Encrypt data
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_length, &encrypt_key, result.iv, AES_ENCRYPT);
    
    // Set the result sizes
    result.encrypted_len = padded_length;

    // Free padded_data as it's no longer needed
    free(padded_data);
    
    return result;
}