#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t enc_data_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    result.encrypted_data = (unsigned char*)malloc(enc_data_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len < 16 ? key_len : 16); // AES key size can be 16, 24, or 32 bytes

    // Inicialitzar l'IV amb dades aleatòries
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        // Maneig d'errors en la generació de l'IV
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    // Copiar la clau
    memcpy(result.key, key, key_len < 16 ? key_len : 16);

    // Configurar la clau d'encriptació
    AES_set_encrypt_key(result.key, 128, &enc_key);

    // Emprar AES en mode CBC per encriptar les dades
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &enc_key, iv, AES_ENCRYPT);

    // Guardar resultats
    result.encrypted_len = enc_data_len;
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    return result;
}