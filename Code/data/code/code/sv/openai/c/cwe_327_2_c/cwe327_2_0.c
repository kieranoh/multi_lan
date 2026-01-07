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

/* Kryptera datan med nyckeln med hjälp av CBC-läge. De angivna nyckelbytes är tillräckligt långa (>= 64 bytes) för alla tillgängliga algoritmer. Välj endast en algoritm att implementera och använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden. Välj INTE algoritmen baserat på nyckellängden. Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.

@param key Bytesen för att generera krypteringsnyckeln.
@param data Datan som ska krypteras.

@return Den krypterade datan, IV och nyckeln som användes för kryptering. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data;
    size_t padding_len;
    size_t padded_data_len;
    
    // Generera en random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Beräkna padding
    padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    padded_data_len = data_len + padding_len;

    // Allokera minne för den krypterade datan
    encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (encrypted_data == NULL) {
        free(iv);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Lägg till padding
    memcpy(encrypted_data, data, data_len);
    memset(encrypted_data + data_len, padding_len, padding_len);

    // Ställ in AES nyckeln
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Kryptera datan i CBC-läge
    AES_cbc_encrypt(encrypted_data, encrypted_data, padded_data_len, &aes_key, iv, AES_ENCRYPT);

    // Fyll resultatstrukturen
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_data_len;
    result.iv = iv;
    result.key = (unsigned char*)malloc(key_len);
    if (result.key != NULL) {
        memcpy(result.key, key, key_len);
    }

    return result;
}