#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Rakenne palautusarvojen säilyttämiseen
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Salakirjoita tiedot avaimella käyttäen AES:ää ja CBC-tilaa.
Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua). Käytä annettujen avainbittien etuliitettä, joka vastaa vaadittua pituutta.
Palauta salattu data, IV (alkuvektori) ja salakirjoituksessa käytetty avain.

@param key Salakirjoitusavaimen luomiseen tarvittavat tavut.
@param data Salakirjoitettava data.

@return Salattu data, IV ja salakirjoituksessa käytetty avain. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY encrypt_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Varataan muisti salatulle datalle
    result.encrypted_data = malloc(padded_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // Muistin varaus epäonnistui
    }

    // Luodaan satunnainen IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // IV:n luonti epäonnistui
    }
    
    // Asetetaan salausavain
    if (AES_set_encrypt_key(key, key_len * 8, &encrypt_key) < 0) {
        free(result.encrypted_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // Avaimen asetuksessa epäonnistui
    }

    // Salakirjoitetaan data CBC-tilassa
    AES_cbc_encrypt(data, result.encrypted_data, padded_len, &encrypt_key, iv, AES_ENCRYPT);

    // Asetetaan palautusarvot
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = malloc(key_len);
    if (result.key != NULL) {
        memcpy(result.key, key, key_len);
    }

    return result;
}