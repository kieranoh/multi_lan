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

/* Encripta les dades amb la clau utilitzant el mode CBC. Els bytes de clau proporcionats són prou llargs (>= 64 bytes) per a tots els algoritmes disponibles. Tria només un algoritme per implementar i utilitza el prefix dels bytes de clau proporcionats que coincideixi amb la longitud requerida. NO triïs l'algoritme en funció de la longitud de la clau. Retorna les dades encriptades, l'IV (vector d'inicialització) i la clau utilitzada per a l'encriptació.

@param key Els bytes per generar la clau d'encriptació.
@param data Les dades a encriptar.

@return Les dades encriptades, l'IV i la clau utilitzada per a l'encriptació. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = (unsigned char*)malloc(data_len + AES_BLOCK_SIZE); // Allocate space for padding
    size_t encrypted_len = 0;

    // Generar un IV aleatori
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }

    // Configurar la clau AES
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }

    // Encriptar les dades
    AES_cbc_encrypt(data, encrypted_data, data_len, &aes_key, iv, AES_ENCRYPT);
    encrypted_len = data_len; // Update length to original data length

    // Assignar resultats
    result.encrypted_data = encrypted_data;
    result.encrypted_len = encrypted_len;
    result.iv = iv;
    result.key = (unsigned char*)malloc(key_len);
    memcpy(result.key, key, key_len); // Copiar la clau a la sortida

    return result;
}