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

/* Šifrirajte podatke s ključem koristeći CBC način. Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta) za sve dostupne algoritme. Odaberite samo jedan algoritam za implementaciju i koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini. NE birajte algoritam na temelju duljine ključa. Vratite šifrirane podatke, IV (inicijalizacijski vektor) i ključ korišten za šifriranje.
@param key Bajtovi za generiranje šifriranog ključa.
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
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);
    
    // Generiranje IV-a
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        result.encrypted_len = 0;
        return result;
    }
    
    // Postavljanje ključa
    memcpy(result.key, key, key_len);
    AES_set_encrypt_key(result.key, 128, &encrypt_key);
    
    // Šifriranje podataka
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &encrypt_key, iv, AES_ENCRYPT);
    
    // Postavljanje rezultata
    result.encrypted_len = padded_len;
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    
    return result;
}