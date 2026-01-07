#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Retourenwerte-Struktur
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Verschlüsseln Sie die Daten mit dem Schlüssel unter Verwendung von AES und CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes). Verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.

@param key Die Bytes zur Generierung des Verschlüsselungsschlüssels.
@param data Die zu verschlüsselnden Daten.

@return Die verschlüsselten Daten, der IV und der für die Verschlüsselung verwendete Schlüssel. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    // Allocate memory for the result
    result.encrypted_data = (unsigned char*)malloc(data_len + AES_BLOCK_SIZE);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(16); // AES-128 uses a 128-bit (16 byte) key

    // Use the first 16 bytes of the key for AES-128
    memcpy(result.key, key, 16);

    // Generate random IV
    if (!RAND_bytes(iv, sizeof(iv))) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result; // Return empty result on failure
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    // Set up AES encryption
    AES_set_encrypt_key(result.key, 128, &aes_key);

    // Padding
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE), AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));

    // Encrypt
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);

    // Clean up
    free(padded_data);

    result.encrypted_len = padded_len;
    return result;
}