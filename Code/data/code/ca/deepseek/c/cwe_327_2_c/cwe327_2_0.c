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
    
    // Comprovacions bàsiques d'entrada
    if (!key || key_len < 16 || !data || data_len == 0) {
        return result;
    }
    
    // Triar AES-256-CBC com a algoritme (segons la documentació, triem només un algoritme)
    const int algorithm = 1; // 1 per AES-256-CBC
    
    if (algorithm == 1) { // AES-256-CBC
        // Longitud de clau per AES-256: 32 bytes (256 bits)
        const size_t aes_key_len = 32;
        const size_t iv_len = AES_BLOCK_SIZE;
        
        // Assegurar que tenim prou bytes de clau
        if (key_len < aes_key_len) {
            return result;
        }
        
        // Reservar memòria per a la clau utilitzada
        result.key = (unsigned char*)malloc(aes_key_len);
        if (!result.key) {
            return result;
        }
        memcpy(result.key, key, aes_key_len);
        
        // Reservar memòria per a l'IV
        result.iv = (unsigned char*)malloc(iv_len);
        if (!result.iv) {
            free(result.key);
            result.key = NULL;
            return result;
        }
        
        // Generar IV aleatori
        if (RAND_bytes(result.iv, iv_len) != 1) {
            free(result.key);
            free(result.iv);
            result.key = NULL;
            result.iv = NULL;
            return result;
        }
        
        // Preparar el context AES
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
            free(result.key);
            free(result.iv);
            result.key = NULL;
            result.iv = NULL;
            return result;
        }
        
        // Calcular la longitud de les dades encriptades (amb padding PKCS#7)
        size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
        result.encrypted_data = (unsigned char*)malloc(padded_len);
        if (!result.encrypted_data) {
            free(result.key);
            free(result.iv);
            result.key = NULL;
            result.iv = NULL;
            return result;
        }
        
        // Copiar les dades originals a un buffer amb padding
        unsigned char* padded_data = (unsigned char*)malloc(padded_len);
        if (!padded_data) {
            free(result.key);
            free(result.iv);
            free(result.encrypted_data);
            result.key = NULL;
            result.iv = NULL;
            result.encrypted_data = NULL;
            return result;
        }
        
        memcpy(padded_data, data, data_len);
        
        // Aplicar padding PKCS#7
        unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
        for (size_t i = data_len; i < padded_len; i++) {
            padded_data[i] = pad_value;
        }
        
        // Encriptar en mode CBC
        unsigned char ivec[AES_BLOCK_SIZE];
        memcpy(ivec, result.iv, AES_BLOCK_SIZE);
        
        AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                       &aes_key, ivec, AES_ENCRYPT);
        
        result.encrypted_len = padded_len;
        
        // Netejar el buffer amb padding
        free(padded_data);
        
        // Netejar la clau AES de la memòria (per seguretat)
        memset(&aes_key, 0, sizeof(AES_KEY));
    }
    
    return result;
}