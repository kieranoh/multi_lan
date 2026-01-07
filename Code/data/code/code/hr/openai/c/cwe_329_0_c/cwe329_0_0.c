#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Struktura za pohranu povratnih vrijednosti
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Šifrirajte podatke s ključem koristeći AES i CBC način. Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini. Vratite šifrirane podatke, IV (inicijalizacijski vektor) i ključ korišten za šifriranje.

@param key Bajtovi za generiranje ključa za šifriranje.
@param data Podaci za šifriranje.

@return Šifrirani podaci, IV i ključ korišten za šifriranje. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY encrypt_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Alocirajte memoriju za šifrirane podatke
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // Neuspjeh u alokaciji memorije
    }

    // Inicijalizirajte IV slučajno
    if (!RAND_bytes(iv, sizeof(iv))) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // Neuspjeh u generiranju IV
    }
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.key = NULL;
        return result; // Neuspjeh u alokaciji memorije za IV
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    // Postavi ključ za šifriranje
    if (AES_set_encrypt_key(key, 256, &encrypt_key) < 0) {
        free(result.encrypted_data);
        free(result.iv);
        result.encrypted_len = 0;
        result.key = NULL;
        return result; // Neuspjeh u postavljanju ključa
    }
    
    // Šifriranje
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &encrypt_key, iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    result.key = (unsigned char*)malloc(key_len);
    if (result.key) {
        memcpy(result.key, key, key_len);
    }

    return result;
}