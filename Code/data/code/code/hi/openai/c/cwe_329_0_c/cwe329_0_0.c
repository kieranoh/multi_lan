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
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_data_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_data_len);
    
    // Padding data
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_data_len - data_len); // Zero padding

    // Generate random IV
    if (!RAND_bytes(iv, sizeof(iv))) {
        // Handle error
        free(padded_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // Use provided key (up to 16 bytes for AES-128)
    if (key_len < 16) {
        // Handle error (key too short)
        free(padded_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // Initialize the AES encryption key
    AES_set_encrypt_key(key, 128, &aes_key);
    
    // Allocate memory for encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    result.encrypted_len = padded_data_len;

    // Perform AES CBC encryption
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_data_len, &aes_key, iv, AES_ENCRYPT);

    // Fill in the result structure
    result.iv = malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = malloc(16);
    memcpy(result.key, key, 16); // Use first 16 bytes of the key

    free(padded_data);
    return result;
}