#include <openssl/aes.h>
#include <openssl/des.h>
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
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Wybieram algorytm AES-256-CBC (stały wybór zgodnie z instrukcją)
    const int algorithm_key_len = 32; // 256 bitów = 32 bajty dla AES-256
    const int iv_len = AES_BLOCK_SIZE; // 16 bajtów dla AES
    
    // Sprawdzenie czy dostarczony klucz jest wystarczająco długi
    if (key_len < algorithm_key_len) {
        return result; // Zwracamy pusty wynik
    }
    
    // Alokacja pamięci dla klucza użytego do szyfrowania
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (result.key == NULL) {
        return result;
    }
    
    // Kopiowanie prefiksu klucza o wymaganej długości
    memcpy(result.key, key, algorithm_key_len);
    
    // Alokacja pamięci dla IV
    result.iv = (unsigned char*)malloc(iv_len);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generowanie losowego IV
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Przygotowanie kontekstu AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Obliczenie rozmiaru zaszyfrowanych danych (dopełnienie do wielokrotności bloku)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Kopiowanie danych wejściowych do bufora z dopełnieniem
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.encrypted_data);
        free(result.key);
        free(result.iv);
        result.encrypted_data = NULL;
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Kopiowanie danych i dodanie dopełnienia PKCS#7
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Szyfrowanie w trybie CBC
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // Czyszczenie bufora z dopełnieniem
    free(padded_data);
    
    return result;
}