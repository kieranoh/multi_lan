#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Enkriptuјte podatke sa ključem koristeći CBC režim.
Dati bajtovi ključa su dovoljno dugi (>= 64 bajta) za sve dostupne algoritme. Izaberite samo jedan algoritam za implementaciju i koristite prefiks datih bajtova ključa koji odgovara potrebnoj dužini. NE birajte algoritam na osnovu dužine ključa.
Vratite enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.

@param key Bajtovi za generisanje ključa za enkripciju.
@param data Podaci za enkripciju.

@return Enkriptovani podaci, IV i ključ koji se koristi za enkripciju. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);
    result.encrypted_data = malloc(padded_len);
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(32); // AES-256 key size
    
    // Generate IV
    if (!RAND_bytes(iv, sizeof(iv))) {
        free(padded_data);
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_len = 0;
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    // Prepare padded data
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Zero padding

    // Use first 32 bytes of key for AES-256
    memcpy(result.key, key, 32);

    // Set encryption key
    AES_set_encrypt_key(result.key, 256, &enc_key);
    
    // Encrypt data
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &enc_key, result.iv, AES_ENCRYPT);

    free(padded_data);
    
    return result;
}