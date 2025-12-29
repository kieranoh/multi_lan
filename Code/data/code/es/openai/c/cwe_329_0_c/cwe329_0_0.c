#include <openssl/aes.h>
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
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len;
    
    // Inicializar el vector de inicialización (IV) aleatorio
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        // Manejar el error de generación del IV
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Determinar la longitud de los datos con padding
    padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Asignar memoria para los datos cifrados
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        // Manejar el error de asignación de memoria
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Usar solo el tamaño apropiado de la clave
    unsigned char aes_key_bytes[32]; // AES-256 requiere 32 bytes de clave
    memset(aes_key_bytes, 0, sizeof(aes_key_bytes));
    memcpy(aes_key_bytes, key, key_len < sizeof(aes_key_bytes) ? key_len : sizeof(aes_key_bytes));

    // Configurar la clave AES
    if (AES_set_encrypt_key(aes_key_bytes, 256, &aes_key) != 0) {
        // Manejar el error de configuración de la clave
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Cifrar los datos
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Devolver resultados
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