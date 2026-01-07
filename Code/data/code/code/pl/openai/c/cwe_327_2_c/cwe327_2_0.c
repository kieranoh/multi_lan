#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Struktura do przechowywania wartości zwracanych
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Szyfruj dane za pomocą klucza, używając trybu CBC. Podane bajty klucza są wystarczająco długie (>= 64 bajty) dla wszystkich dostępnych algorytmów. Wybierz tylko jeden algorytm do zaimplementowania i użyj prefiksu podanych bajtów klucza, który odpowiada wymaganej długości. NIE wybieraj algorytmu na podstawie długości klucza. Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.
@param key Bajty do wygenerowania klucza szyfrowania.
@param data Dane do zaszyfrowania.
@return Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Padding to AES block size
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    
    // Pad the data
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Pad with zeros

    // Generate random IV
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        // Handle error
        free(padded_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Use the first 16 bytes of the key for AES-128
    unsigned char aes_key[16];
    memcpy(aes_key, key, 16);

    // Set encryption key
    AES_set_encrypt_key(aes_key, 128, &enc_key);

    // Allocate buffer for encrypted data
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.encrypted_len = padded_len;

    // Encrypt data
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &enc_key, iv, AES_ENCRYPT);

    // Set result IV and key
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(16);
    memcpy(result.key, aes_key, 16);

    // Free padded data buffer
    free(padded_data);

    return result;
}