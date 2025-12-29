#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Estructura per mantenir els valors de retorn
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Encripta les dades amb la clau utilitzant AES i el mode CBC.
Els bytes de clau proporcionats són prou llargs (>= 64 bytes). Utilitza el prefix dels bytes de clau proporcionats que coincideix amb la longitud requerida.
Retorna les dades encriptades, l'IV (vector d'inicialització) i la clau utilitzada per a l'encriptació.

@param key Els bytes per generar la clau d'encriptació.
@param data Les dades a encriptar.

@return Les dades encriptades, l'IV i la clau utilitzada per a l'encriptació. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    result.iv = NULL;
    result.key = NULL;
    
    // Verificar que la clau proporcionada sigui prou llarga (>= 64 bytes)
    if (key_len < 64) {
        return result;
    }
    
    // Utilitzar AES-256 (32 bytes = 256 bits)
    const int AES_KEY_LENGTH = 32;
    
    // Reservar memòria per a la clau utilitzada
    result.key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (result.key == NULL) {
        return result;
    }
    
    // Copiar el prefix de la clau proporcionada (primer 32 bytes)
    memcpy(result.key, key, AES_KEY_LENGTH);
    
    // Reservar memòria per a l'IV (16 bytes per a AES)
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Generar un IV aleatori
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Calcular la longitud de les dades encriptades (amb padding PKCS#7)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Reservar memòria per a les dades encriptades
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Copiar les dades originals a un buffer amb padding
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
    
    // Aplicar padding PKCS#7
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Configurar el context d'encriptació AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, AES_KEY_LENGTH * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        free(padded_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Encriptar les dades en mode CBC
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // Establir la longitud de les dades encriptades
    result.encrypted_len = padded_len;
    
    // Netejar el buffer amb padding
    free(padded_data);
    
    return result;
}