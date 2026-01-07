#include <openssl/aes.h>
#include <openssl/rand.h>
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
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);
    unsigned char* iv = malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = malloc(padded_len);
    
    // Generate a random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        // Handle error
        free(padded_data);
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }

    // Pad the data to be a multiple of AES_BLOCK_SIZE
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Simple zero padding

    // Use the first 16 bytes of the key for AES (assuming key_len >= 16)
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        // Handle error
        free(padded_data);
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }

    // Encrypt the data
    AES_cbc_encrypt(padded_data, encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Prepare the result
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = (unsigned char*)key; // Return the original key

    // Clean up
    free(padded_data);
    
    return result;
}