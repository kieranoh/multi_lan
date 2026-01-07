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
    
    // Controleer geldige invoerparameters
    if (key == NULL || data == NULL || key_len < 16 || data_len == 0) {
        return result;
    }
    
    // Kies AES-256-CBC als algoritme (zoals gespecificeerd in de opdracht)
    const int algorithm_key_len = 32; // AES-256 vereist 32 bytes (256 bits)
    const int iv_len = AES_BLOCK_SIZE; // AES heeft 16 bytes IV
    
    // Controleer of de sleutel lang genoeg is
    if (key_len < algorithm_key_len) {
        return result;
    }
    
    // Allocateer geheugen voor de gebruikte sleutel (eerste 32 bytes van de opgegeven sleutel)
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (result.key == NULL) {
        return result;
    }
    memcpy(result.key, key, algorithm_key_len);
    
    // Allocateer geheugen voor de IV
    result.iv = (unsigned char*)malloc(iv_len);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Genereer een willekeurige IV
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Bereken de benodigde uitvoergrootte (gepadded naar AES blokgrootte)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Kopieer de invoergegevens naar een tijdelijke buffer voor padding
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
    
    // Kopieer de originele data en voeg PKCS#7 padding toe
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Initialiseer AES sleutel en context
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        free(padded_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Voer AES-CBC versleuteling uit
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    // Stel de versleutelde lengte in
    result.encrypted_len = padded_len;
    
    // Ruim de tijdelijke buffer op
    free(padded_data);
    
    return result;
}