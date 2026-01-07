#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    result.iv = NULL;
    result.key = NULL;
    
    // Tarkistetaan että avain on tarpeeksi pitkä (>= 64 tavua = 512 bittiä)
    if (key_len < 64) {
        return result;
    }
    
    // Käytetään avaimen etuliitettä (32 tavua = 256 bittiä)
    size_t aes_key_len = 32; // AES-256
    unsigned char* aes_key = (unsigned char*)malloc(aes_key_len);
    if (!aes_key) {
        return result;
    }
    memcpy(aes_key, key, aes_key_len);
    
    // Varataan muisti IV:lle (16 tavua AES CBC:lle)
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!iv) {
        free(aes_key);
        return result;
    }
    
    // Generoidaan satunnainen IV
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Lasketaan salatun datan koko (täytetään AES_BLOCK_SIZE:n monikoksi)
    size_t padded_len = data_len;
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    padded_len += padding;
    
    // Varataan muisti salatulle datalle
    unsigned char* encrypted_data = (unsigned char*)malloc(padded_len);
    if (!encrypted_data) {
        free(aes_key);
        free(iv);
        return result;
    }
    
    // Kopioidaan alkuperäinen data ja lisätään padding
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(aes_key);
        free(iv);
        free(encrypted_data);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    // PKCS#7 padding
    for (size_t i = 0; i < padding; i++) {
        padded_data[data_len + i] = (unsigned char)padding;
    }
    
    // Alustetaan AES konteksti
    AES_KEY aes_key_struct;
    if (AES_set_encrypt_key(aes_key, aes_key_len * 8, &aes_key_struct) != 0) {
        free(aes_key);
        free(iv);
        free(encrypted_data);
        free(padded_data);
        return result;
    }
    
    // Suoritetaan salaus CBC-tilassa
    AES_cbc_encrypt(padded_data, encrypted_data, padded_len, &aes_key_struct, iv, AES_ENCRYPT);
    
    // Täytetään tulosrakenne
    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = aes_key;
    
    // Vapautetaan väliaikaiset muistialueet
    free(padded_data);
    
    return result;
}