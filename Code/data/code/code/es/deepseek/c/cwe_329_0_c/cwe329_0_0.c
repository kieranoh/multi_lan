#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar los valores de retorno
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Cifra los datos con la clave usando AES y modo CBC.
Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes). Usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida.
Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.

@param key Los bytes para generar la clave de cifrado.
@param data Los datos a cifrar.

@return Los datos cifrados, el IV y la clave utilizada para la cifrado. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Verificar parámetros de entrada
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Longitud de clave AES-256 (32 bytes = 256 bits)
    const size_t aes_key_len = 32;
    
    // Asignar memoria para la clave AES
    result.key = (unsigned char*)malloc(aes_key_len);
    if (result.key == NULL) {
        return result;
    }
    
    // Usar el prefijo de los bytes de clave proporcionados
    memcpy(result.key, key, aes_key_len);
    
    // Asignar memoria para el IV (16 bytes para AES)
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generar IV aleatorio
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Calcular tamaño del texto cifrado (redondeado al múltiplo del tamaño de bloque)
    size_t padded_len = data_len;
    if (data_len % AES_BLOCK_SIZE != 0) {
        padded_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    }
    
    // Asignar memoria para los datos cifrados
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
    if (AES_set_encrypt_key(result.key, aes_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Realizar cifrado CBC
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    return result;
}