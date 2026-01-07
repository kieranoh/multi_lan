#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    AES_KEY encrypt_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Initialize the result
    result.encrypted_data = malloc(padded_len);
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(key_len);
    
    // Generate a random IV
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        // Handle error
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // Use the provided key (truncate or pad it if necessary)
    memcpy(result.key, key, key_len);
    
    // Set encryption key
    AES_set_encrypt_key(result.key, key_len * 8, &encrypt_key);
    
    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &encrypt_key, result.iv, AES_ENCRYPT);
    
    return result;
}