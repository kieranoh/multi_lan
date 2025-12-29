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
    result.encrypted_data = NULL;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(16); // AES uses a key length of 16 bytes for AES-128

    // Generate a random IV
    if (!RAND_bytes(result.iv, AES_BLOCK_SIZE)) {
        // Handle error
        free(result.iv);
        free(result.key);
        return result;
    }

    // Create AES encryption context
    AES_KEY enc_key;
    if (AES_set_encrypt_key(key, 128, &enc_key) < 0) {
        // Handle error
        free(result.iv);
        free(result.key);
        return result;
    }

    // Calculate the size of the padding required
    size_t padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_data_len = data_len + padding_len;

    // Allocate memory for the encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (result.encrypted_data == NULL) {
        // Handle memory allocation error
        free(result.iv);
        free(result.key);
        return result;
    }

    // Copy the data to the encrypted data buffer and apply padding
    memcpy(result.encrypted_data, data, data_len);
    memset(result.encrypted_data + data_len, padding_len, padding_len);

    // Perform encryption in CBC mode
    AES_cbc_encrypt(result.encrypted_data, result.encrypted_data, padded_data_len, &enc_key, result.iv, AES_ENCRYPT);

    // Set the output lengths
    result.encrypted_len = padded_data_len;
    memcpy(result.key, key, 16); // Store the first 16 bytes of key

    return result;
}