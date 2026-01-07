#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Rakenteet palautusarvojen säilyttämiseen
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Salakirjoita tiedot avaimella käyttäen CBC-tilaa.
Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua) kaikille saatavilla oleville algoritmeille. Valitse vain yksi algoritmi toteutettavaksi ja käytä annettujen avainbittien prefiksiä, joka vastaa vaadittua pituutta. Älä valitse algoritmia avaimen pituuden perusteella.
Palauta salattu data, IV (alkuvaroitusvektori) ja salakirjoituksessa käytetty avain.

@param key Salakirjoitusavaimen luomiseen käytettävät tavut.
@param data Salakirjoitettavat tiedot.

@return Salattu data, IV ja salakirjoituksessa käytetty avain. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    size_t aes_key_len = 32; // Käytetään AES-256 -salakirjoitusta
    unsigned char aes_key[aes_key_len];
    unsigned char iv[AES_BLOCK_SIZE];

    // Luodaan alustusvektori
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Valitaan avaimen pituuden mukaan oikea osa avaimesta
    if (key_len >= aes_key_len) {
        memcpy(aes_key, key, aes_key_len);
    } else {
        memcpy(aes_key, key, key_len);
        memset(aes_key + key_len, 0, aes_key_len - key_len);
    }

    // Luo AES-salakirjoitusobjekti
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key, aes_key_len * 8, &encrypt_key);

    // Lasketaan salatun datan pituus
    size_t padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_data_len = data_len + padding_len;

    // Allokoidaan muisti salatulle datalle
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Lisätään padding
    memcpy(result.encrypted_data, data, data_len);
    memset(result.encrypted_data + data_len, padding_len, padding_len);

    // Salakirjoitetaan data CBC-tilassa
    unsigned char* encrypted_ptr = result.encrypted_data;
    for (size_t i = 0; i < padded_data_len; i += AES_BLOCK_SIZE) {
        if (i == 0) {
            // Ensimmäinen lohko: XOR-ataan IV:n kanssa
            for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
                encrypted_ptr[j] = encrypted_ptr[j] ^ iv[j];
            }
        } else {
            // Muut lohkot: XOR-ataan edellisen salatun lohkon kanssa
            for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
                encrypted_ptr[j] = encrypted_ptr[j] ^ encrypted_ptr[i - AES_BLOCK_SIZE + j];
            }
        }
        AES_encrypt(encrypted_ptr, encrypted_ptr, &encrypt_key);
        encrypted_ptr += AES_BLOCK_SIZE;
    }

    // Asetetaan tulokset
    result.encrypted_len = padded_data_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = (unsigned char*)malloc(aes_key_len);
    if (result.key != NULL) {
        memcpy(result.key, aes_key, aes_key_len);
    }

    return result;
}