#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Struktura do przechowywania wartości zwracanych
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Szyfruj dane za pomocą klucza, używając AES i trybu CBC.
Podany klucz bajtów jest wystarczająco długi (>= 64 bajty). Użyj prefiksu podanych bajtów klucza, który odpowiada wymaganemu rozmiarowi.
Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.

@param key Bajty do wygenerowania klucza szyfrowania.
@param data Dane do zaszyfrowania.

@return Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Inicjalizacja wektora inicjalizacji
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Ustal rozmiar klucza
    unsigned char aes_key_bytes[32]; // 256-bit key
    memcpy(aes_key_bytes, key, key_len < 32 ? key_len : 32);
    
    // Ustawienie klucza AES
    if (AES_set_encrypt_key(aes_key_bytes, 256, &aes_key) < 0) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Przygotowanie pamięci na zaszyfrowane dane
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Szyfrowanie danych
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = (unsigned char*)malloc(32);
    if (result.key != NULL) {
        memcpy(result.key, aes_key_bytes, 32);
    }

    return result;
}