#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Structure to hold the return values
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/**
 * Encrypt the data with the key using CBC mode.
 * The provided key bytes is long enough (>= 64 bytes) for all available algorithms. 
 * Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. 
 * Do NOT choose the algorithm based on the length of the key.
 * Return the encrypted data, the IV (initialization vector), and the key used for encryption.
 *
 * @param key The bytes to generate the encryption key.
 * @param data The data to encrypt.
 * @return The encrypted data, the IV, and the key used for encryption.
 */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_data_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Allocate memory for the encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Generate random IV
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Set the key (AES-128 requires a 16-byte key)
    if (key_len >= 16) {
        memcpy(result.key, key, 16);
        AES_set_encrypt_key(result.key, 128, &aes_key);
    }

    // Perform the encryption
    AES_cbc_encrypt(data, result.encrypted_data, padded_data_len, &aes_key, iv, AES_ENCRYPT);
    
    // Set return values
    result.encrypted_len = padded_data_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    return result;
}