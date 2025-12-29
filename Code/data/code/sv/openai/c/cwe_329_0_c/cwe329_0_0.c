#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Struktur för att hålla returvärden
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Kryptera datan med nyckeln med hjälp av AES och CBC-läge. De angivna nyckelbytes är tillräckligt långa (>= 64 bytes). 
   Använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden. 
   Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.

   @param key Bytesen för att generera krypteringsnyckeln.
   @param data Datan som ska krypteras.
   @return Den krypterade datan, IV och nyckeln som användes för kryptering.
*/
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data;
    size_t encrypted_len;
    
    // Generera en slumpmässig IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        // Hantera fel vid generering av IV
        free(iv);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Förbereda nyckeln
    unsigned char aes_key_buffer[32]; // 256 bitar nyckel
    if (key_len >= 32) {
        memcpy(aes_key_buffer, key, 32);
    } else {
        memcpy(aes_key_buffer, key, key_len);
        memset(aes_key_buffer + key_len, 0, 32 - key_len); // Fyll med nollor
    }

    // Initiera AES
    AES_set_encrypt_key(aes_key_buffer, 256, &aes_key);

    // Beräkna padding och allokera minne för krypterad data
    int padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    encrypted_len = data_len + padding;
    encrypted_data = (unsigned char*)malloc(encrypted_len);

    // Kopiera data och applicera padding
    unsigned char* padded_data = (unsigned char*)malloc(encrypted_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding, padding); // Fyll padding

    // Kryptera data
    AES_cbc_encrypt(padded_data, encrypted_data, encrypted_len, &aes_key, iv, AES_ENCRYPT);

    // Frigör minne
    free(padded_data);

    // Fyll i resultatet
    result.encrypted_data = encrypted_data;
    result.encrypted_len = encrypted_len;
    result.iv = iv;
    result.key = (unsigned char*)malloc(32);
    memcpy(result.key, aes_key_buffer, 32); // Kopiera nyckeln

    return result;
}