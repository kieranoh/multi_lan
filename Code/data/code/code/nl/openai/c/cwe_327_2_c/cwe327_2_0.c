#include <openssl/aes.h>
#include <openssl/des.h>
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

/* Versleutel de gegevens met de sleutel met behulp van CBC-modus.
De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes) voor alle beschikbare algoritmen. Kies slechts één algoritme om te implementeren en gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte. Kies het algoritme NIET op basis van de lengte van de sleutel.
Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.

@param key De bytes om de versleuteling sleutel te genereren.
@param data De te versleutelen gegevens.

@return De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padding_len;
    size_t padded_data_len;

    // Initialiseer de IV
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        return result; // Fout bij genereren van IV
    }

    // Bereken de lengte van de gegevens na padding
    padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    padded_data_len = data_len + padding_len;

    // Alloceer geheugen voor versleutelde gegevens
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_data = NULL;
        return result; // Geheugenallocatie mislukt
    }

    // Voeg padding toe aan de gegevens
    memcpy(result.encrypted_data, data, data_len);
    memset(result.encrypted_data + data_len, padding_len, padding_len);

    // Stel de AES sleutel in
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result; // Fout bij instellen van de sleutel
    }

    // Versleutel de gegevens in CBC-modus
    AES_cbc_encrypt(result.encrypted_data, result.encrypted_data, padded_data_len, &aes_key, iv, AES_ENCRYPT);

    // Vul de struct met de resultaten
    result.encrypted_len = padded_data_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    if (result.iv == NULL || result.key == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result; // Geheugenallocatie mislukt
    }

    // Kopieer IV en sleutel naar de return struct
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    memcpy(result.key, key, key_len);

    return result;
}