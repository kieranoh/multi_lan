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

/* Encrypts the data using the key with AES in CBC mode.
The provided key bytes are long enough (>= 64 bytes). Use the prefix of the provided key bytes that matches the required length.
Returns the encrypted data, the IV (initialization vector), and the key used for encryption.

@param key The bytes to generate the encryption key.
@param key_len The length of the key.
@param data The data to be encrypted.
@param data_len The length of the data to be encrypted.

@return The encrypted data, the IV, and the key used for encryption. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    // Ensure the key is of proper length (128, 192, or 256 bits)
    if (key_len < 16) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Generate a random IV
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Use the first 16 bytes of the key for AES-128
    unsigned char aes_key_bytes[16];
    memcpy(aes_key_bytes, key, 16);

    // Set the encryption key
    AES_set_encrypt_key(aes_key_bytes, 128, &aes_key);

    // Calculate the length of the padded data
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    result.encrypted_data = malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Perform encryption
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = malloc(16);
    if (result.key != NULL) {
        memcpy(result.key, aes_key_bytes, 16);
    }

    return result;
}