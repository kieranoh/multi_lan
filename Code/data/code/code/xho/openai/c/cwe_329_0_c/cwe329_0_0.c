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
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len, encrypted_len;
    
    // Ensure the key is at least 16 bytes long for AES-128
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

    // Prepare the key (use the prefix based on required length)
    unsigned char encryption_key[16]; // AES-128 requires a 16-byte key
    memcpy(encryption_key, key, 16);

    // Pad the data to be a multiple of AES_BLOCK_SIZE
    padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Zero padding

    // Set the encryption key
    AES_set_encrypt_key(encryption_key, 128, &enc_key);

    // Allocate memory for encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(padded_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &enc_key, iv, AES_ENCRYPT);

    // Set the result values
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(16);
    memcpy(result.key, encryption_key, 16);

    // Clean up
    free(padded_data);
    
    return result;
}