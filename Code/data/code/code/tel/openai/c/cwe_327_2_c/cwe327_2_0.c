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
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    result.encrypted_data = malloc(padded_len);
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(key_len);

    if (!result.encrypted_data || !result.iv || !result.key) {
        // Handle memory allocation failure
        result.encrypted_len = 0;
        return result;
    }

    // Copy the key and generate a random IV
    memcpy(result.key, key, key_len);
    RAND_bytes(iv, AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    // Set the encryption key
    AES_set_encrypt_key(result.key, 128, &aes_key); // Using 128-bit AES

    // Perform the encryption
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;
    return result;
}