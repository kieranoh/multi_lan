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
    encryption_result result = { NULL, 0, NULL, NULL };
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];

    // Generate a random IV
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        return result; // Return empty result on failure
    }

    // Set the key for AES encryption
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        return result; // Return empty result on failure
    }

    // Calculate the length for the encrypted data
    result.encrypted_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(16); // AES key size (128 bits = 16 bytes)

    if (!result.encrypted_data || !result.iv || !result.key) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result; // Return empty result on memory allocation failure
    }

    // Copy the IV and key to the result
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    memcpy(result.key, key, 16); // Assuming 128-bit AES key

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, result.iv, AES_ENCRYPT);

    return result; // Return the result with encrypted data, IV, and key
}