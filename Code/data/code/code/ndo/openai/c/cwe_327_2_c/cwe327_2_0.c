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
    encryption_result result;
    AES_KEY aes_key;
    size_t block_size = AES_BLOCK_SIZE;
    size_t padded_len = ((data_len + block_size - 1) / block_size) * block_size;
    
    // Allocate memory for the encrypted data, IV, and the key
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(block_size);
    result.key = (unsigned char*)malloc(32); // AES-256 requires a 32-byte key

    // Copy the first 32 bytes of the provided key to the AES key
    memcpy(result.key, key, 32);

    // Generate a random IV
    if (RAND_bytes(result.iv, block_size) != 1) {
        // Handle error
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    // Set the encryption key
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        // Handle error
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    // Perform AES CBC encryption
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, result.iv, AES_ENCRYPT);

    // Set the encrypted length
    result.encrypted_len = padded_len;

    return result;
}