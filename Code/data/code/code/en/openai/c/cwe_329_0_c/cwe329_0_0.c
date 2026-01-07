#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold the return values
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/**
Encrypt the data with the key using AES and CBC mode.
The provided key bytes is long enough (>= 64 bytes). Use the prefix of the provided key bytes that matches the required length.
Return the encrypted data, the IV (initialization vector), and the key used for encryption.

@param key The bytes to generate the encryption key.
@param data The data to encrypt.

@return The encrypted data, the IV, and the key used for encryption.
*/
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY encrypt_key;
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    size_t enc_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Pad to block size

    result.encrypted_data = (unsigned char*)malloc(enc_len);
    result.encrypted_len = enc_len;
    result.iv = iv;
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);

    // Generate a random IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(result.encrypted_data);
        free(iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result; // Failed to generate IV
    }
    
    // Set the key for encryption
    if (key_len >= AES_BLOCK_SIZE) {
        memcpy(result.key, key, AES_BLOCK_SIZE);
    } else {
        memcpy(result.key, key, key_len);
        memset(result.key + key_len, 0, AES_BLOCK_SIZE - key_len); // Pad key if necessary
    }

    // Initialize the AES key for encryption
    AES_set_encrypt_key(result.key, 128, &encrypt_key); // 128-bit key length

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &encrypt_key, iv, AES_ENCRYPT);

    return result;
}