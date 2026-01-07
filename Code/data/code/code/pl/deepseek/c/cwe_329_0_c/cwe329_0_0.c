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
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    result.iv = NULL;
    result.key = NULL;
    
    // Sprawdzenie poprawności danych wejściowych
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Rozmiar klucza dla AES-256 (32 bajty = 256 bitów)
    const size_t AES_KEY_SIZE = 32;
    
    // Rozmiar IV dla trybu CBC (16 bajtów = 128 bitów)
    const size_t IV_SIZE = 16;
    
    // Alokacja pamięci dla klucza
    result.key = (unsigned char*)malloc(AES_KEY_SIZE);
    if (result.key == NULL) {
        return result;
    }
    
    // Kopiowanie pierwszych AES_KEY_SIZE bajtów z podanego klucza
    memcpy(result.key, key, AES_KEY_SIZE);
    
    // Alokacja pamięci dla IV
    result.iv = (unsigned char*)malloc(IV_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generowanie losowego IV
    if (RAND_bytes(result.iv, IV_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Obliczenie rozmiaru zaszyfrowanych danych (dopasowanie do wielokrotności bloku AES)
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    result.encrypted_len = padded_len;
    
    // Alokacja pamięci dla zaszyfrowanych danych
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Inicjalizacja kontekstu AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Kopiowanie danych wejściowych do bufora z paddingu
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // Dodanie paddingu PKCS#7
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Szyfrowanie danych w trybie CBC
    unsigned char iv_copy[IV_SIZE];
    memcpy(iv_copy, result.iv, IV_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    // Czyszczenie pamięci tymczasowej
    free(padded_data);
    
    return result;
}