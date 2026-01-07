#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Valitaan AES-256-CBC algoritmi (käytetään avaimen 32 ensimmäistä tavua)
    const int ALGORITHM_KEY_LEN = 32; // AES-256 vaatii 32 tavua
    const int IV_LEN = AES_BLOCK_SIZE; // 16 tavua AES:lle
    
    // Varmistetaan että avain on tarpeeksi pitkä
    if (key_len < ALGORITHM_KEY_LEN) {
        return result;
    }
    
    // Varataan muistia tuloksille
    result.key = (unsigned char*)malloc(ALGORITHM_KEY_LEN);
    result.iv = (unsigned char*)malloc(IV_LEN);
    
    if (!result.key || !result.iv) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Kopioidaan avaimen ensimmäiset 32 tavua
    memcpy(result.key, key, ALGORITHM_KEY_LEN);
    
    // Luodaan satunnainen IV
    if (RAND_bytes(result.iv, IV_LEN) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Lasketaan salatun datan koko (täytetty AES_BLOCK_SIZE:n monikerraksi)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Kopioidaan alkuperäinen data väliaikaiseen puskuriin täytettä varten
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // Täytetään PKCS#7-menetelmällä
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Alustetaan AES konteksti
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, ALGORITHM_KEY_LEN * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        free(padded_data);
        return result;
    }
    
    // Suoritetaan salaus CBC-tilassa
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // Siivotaan väliaikainen puskuri
    free(padded_data);
    
    return result;
}