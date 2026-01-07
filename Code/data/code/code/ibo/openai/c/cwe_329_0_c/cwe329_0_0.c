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
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = (unsigned char*)malloc(data_len + AES_BLOCK_SIZE);
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Generate random IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Use the prefix of the key for AES
    unsigned char aes_key[32]; // AES supports key sizes of 128, 192, and 256 bits
    memcpy(aes_key, key, key_len < sizeof(aes_key) ? key_len : sizeof(aes_key));

    // Set encryption key
    AES_set_encrypt_key(aes_key, 256, &enc_key);

    // Perform AES CBC encryption
    AES_cbc_encrypt(data, encrypted_data, padded_len, &enc_key, iv, AES_ENCRYPT);

    // Populate the result structure
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = (unsigned char*)malloc(32); // Allocate memory for the key
    memcpy(result.key, aes_key, sizeof(aes_key)); // Store the key used for encryption

    return result;
}