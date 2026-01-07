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
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = NULL;
    size_t padded_data_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;

    // Generate a random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(iv);
        // Handle error
    }

    // Prepare the AES key (use first 16 bytes for AES-128)
    unsigned char aes_key_buffer[16];
    memcpy(aes_key_buffer, key, 16);
    AES_set_encrypt_key(aes_key_buffer, 128, &aes_key);

    // Allocate memory for the encrypted data
    encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (!encrypted_data) {
        free(iv);
        // Handle error
    }

    // Pad the data
    unsigned char* padded_data = (unsigned char*)malloc(padded_data_len);
    memset(padded_data, 0, padded_data_len);
    memcpy(padded_data, data, data_len);
    // Padding with PKCS#7
    for (size_t i = data_len; i < padded_data_len; i++) {
        padded_data[i] = padded_data_len - data_len;
    }

    // Encrypt the data
    AES_cbc_encrypt(padded_data, encrypted_data, padded_data_len, &aes_key, iv, AES_ENCRYPT);

    // Set the result
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_data_len;
    result.iv = iv;
    result.key = (unsigned char*)malloc(16);
    memcpy(result.key, aes_key_buffer, 16);

    // Clean up
    free(padded_data);

    return result;
}