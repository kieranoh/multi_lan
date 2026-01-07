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
    
    // Validar parámetros de entrada
    if (key == NULL || data == NULL || key_len < 16) {
        return result;
    }
    
    // Elegir AES-256-CBC como algoritmo (usando los primeros 32 bytes de la clave)
    const int ALGORITHM_KEY_LEN = 32; // AES-256 requiere 32 bytes (256 bits)
    const int IV_LEN = AES_BLOCK_SIZE; // 16 bytes para AES
    
    // Asignar memoria para la clave utilizada
    result.key = (unsigned char*)malloc(ALGORITHM_KEY_LEN);
    if (result.key == NULL) {
        return result;
    }
    
    // Copiar los primeros ALGORITHM_KEY_LEN bytes de la clave proporcionada
    memcpy(result.key, key, ALGORITHM_KEY_LEN);
    
    // Asignar memoria para el IV
    result.iv = (unsigned char*)malloc(IV_LEN);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generar IV aleatorio
    if (RAND_bytes(result.iv, IV_LEN) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Calcular el tamaño del texto cifrado (múltiplo del tamaño de bloque)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Inicializar contexto AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, ALGORITHM_KEY_LEN * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Realizar cifrado AES-CBC
    // Copiar datos de entrada para el padding manual
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
    
    // Copiar datos originales
    memcpy(padded_data, data, data_len);
    
    // Aplicar padding PKCS#7
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Cifrar en modo CBC
    unsigned char iv_copy[IV_LEN];
    memcpy(iv_copy, result.iv, IV_LEN);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                    &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // Limpiar datos temporales
    free(padded_data);
    
    return result;
}