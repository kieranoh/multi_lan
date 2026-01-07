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
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    
    // Generate a random IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        // Handle error
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Use the first 16 bytes of the key for AES
    memcpy(result.key, key, AES_BLOCK_SIZE);

    // Allocate memory for the encrypted data
    result.encrypted_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);

    // Create and initialize the AES encryption context
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(result.key, 128, &encrypt_key) < 0) {
        // Handle error
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &encrypt_key, result.iv, AES_ENCRYPT);

    return result;
}