#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Struktura za čuvanje povratnih vrednosti
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Enkriptuјte podatke sa ključem koristeći AES i CBC mod.
Dati bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks datih bajtova ključa koji odgovara potrebnoj dužini.
Vratite enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.

@param key Bajtovi za generisanje ključa za enkripciju.
@param data Podaci za enkripciju.

@return Enkriptovani podaci, IV i ključ korišćen za enkripciju. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY encrypt_key;
    unsigned char* encrypted_data;
    unsigned char iv[AES_BLOCK_SIZE];

    // Alocirajte prostor za enkriptovane podatke
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    encrypted_data = (unsigned char*)malloc(padded_len);
    if (encrypted_data == NULL) {
        // U slučaju greške u alokaciji, postavite dužinu na 0
        result.encrypted_len = 0;
        return result;
    }

    // Generišite nasumični IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(encrypted_data);
        result.encrypted_len = 0;
        return result;
    }

    // Postavite ključ za enkripciju
    if (AES_set_encrypt_key(key, key_len * 8, &encrypt_key) < 0) {
        free(encrypted_data);
        result.encrypted_len = 0;
        return result;
    }

    // Izvršite enkripciju u CBC modu
    AES_cbc_encrypt(data, encrypted_data, padded_len, &encrypt_key, iv, AES_ENCRYPT);

    // Popunite rezultat
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = (unsigned char*)malloc(key_len);
    if (result.key != NULL) {
        memcpy(result.key, key, key_len);
    }

    return result;
}