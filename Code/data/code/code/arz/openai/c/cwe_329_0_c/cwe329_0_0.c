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
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE]; // IV buffer
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Padding length
    unsigned char* padded_data = malloc(padded_len);

    // Create padding
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Zero padding (for simplicity)

    // Generate random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(padded_data);
        memset(&result, 0, sizeof(result)); // Clear result on failure
        return result; // Return empty result on failure
    }

    // Use the first 16 bytes of the provided key for AES-128
    unsigned char aes_key[16];
    memcpy(aes_key, key, 16);

    // Initialize encryption
    AES_set_encrypt_key(aes_key, 128, &enc_key); // 128-bit key

    // Allocate memory for encrypted data
    result.encrypted_data = malloc(padded_len);
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(16); // Store the key used

    // Copy IV and key to result
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    memcpy(result.key, aes_key, 16);

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &enc_key, iv, AES_ENCRYPT);

    // Clean up
    free(padded_data);

    return result; // Return the result containing encrypted data, iv, and key
}