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
    const size_t AES_KEY_LENGTH = 16; // AES-128
    const size_t AES_BLOCK_SIZE = AES_BLOCK_SIZE;

    // Allocate memory for the IV and the encrypted data
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(AES_KEY_LENGTH);
    
    // Use the first 16 bytes of the key for AES
    memcpy(result.key, key, AES_KEY_LENGTH);

    // Generate a random IV
    if (!RAND_bytes(result.iv, AES_BLOCK_SIZE)) {
        // Handle error
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Calculate the required length for padding
    size_t padding_length = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_data_len = data_len + padding_length;

    // Allocate memory for padded data and the encrypted data
    unsigned char* padded_data = malloc(padded_data_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding_length, padding_length); // Add padding

    result.encrypted_data = malloc(padded_data_len);
    AES_KEY aes_key;
    AES_set_encrypt_key(result.key, 128, &aes_key); // Set AES key for encryption

    // Encrypt the data using AES CBC mode
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_data_len, &aes_key, result.iv, AES_ENCRYPT);

    // Set the encrypted length
    result.encrypted_len = padded_data_len;

    // Free the padded data as it's no longer needed
    free(padded_data);

    return result;
}