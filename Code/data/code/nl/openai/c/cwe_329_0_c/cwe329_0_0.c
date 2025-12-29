#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Structuur om de retourwaarden vast te houden
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Versleutel de gegevens met de sleutel met behulp van AES en CBC-modus.
De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes). Gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte.
Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.

@param key De bytes om de versleuteling sleutel te genereren.
@param data De te versleutelen gegevens.

@return De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];

    // Genereer een random IV
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Gebruik de eerste 32 bytes van de sleutel voor AES-256
    unsigned char aes_key[32];
    memcpy(aes_key, key, 32);

    // Initialiseer de AES sleutel
    AES_set_encrypt_key(aes_key, 256, &enc_key);

    // Padding van data voor AES
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Kopieer de gegevens en vul aan met padding
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE), AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));

    // Versleutel de gegevens
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(padded_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Voer de versleuteling uit
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &enc_key, iv, AES_ENCRYPT);

    // Vul het resultaat in
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = (unsigned char*)malloc(32);
    if (result.key != NULL) {
        memcpy(result.key, aes_key, 32);
    }

    // Opruimen
    free(padded_data);

    return result;
}