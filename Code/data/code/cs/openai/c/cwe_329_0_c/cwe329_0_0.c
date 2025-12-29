#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Struktura pro uchování návratových hodnot
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Zašifrujte data s klíčem pomocí AES a režimu CBC.
Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů). Použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce.
Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.

@param key Bajty pro generování šifrovacího klíče.
@param data Data k zašifrování.

@return Zašifrovaná data, IV a klíč použitý pro šifrování. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY encrypt_key;
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);
    unsigned char* iv = malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = malloc(padded_len);
    
    // Generate random IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(padded_data);
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Pad the data
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Simple padding (could use PKCS#7)

    // Set AES key (assuming key_len is a valid AES key length)
    if (AES_set_encrypt_key(key, key_len * 8, &encrypt_key) < 0) {
        free(padded_data);
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Encrypt the data
    AES_cbc_encrypt(padded_data, encrypted_data, padded_len, &encrypt_key, iv, AES_ENCRYPT);

    // Prepare result
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = (unsigned char*)key; // Returning the key used (should be handled securely)

    // Free the padded data (it is no longer needed)
    free(padded_data);

    return result;
}