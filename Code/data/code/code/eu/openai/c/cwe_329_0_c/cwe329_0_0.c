#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>

// Itzultze-balioak gordetzeko egitura
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Datuak gakoarekin AES eta CBC moduan enkriptatu.
Emandako gako byteak nahikoa luzeak dira (>= 64 byte). Erabili emandako gako byteen aurprefikua behar den luzera egokitzen dena.
Itzuli enkriptatutako datuak, IV (hasierako bideratzailea) eta enkriptatzeko erabilitako gakoa.

@param key Enkriptatzeko gakoa sortzeko byteak.
@param data Enkriptatu beharreko datuak.

@return Enkriptatutako datuak, IV eta enkriptatzeko erabilitako gakoa. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY enc_key;
    size_t enc_data_len;
    unsigned char iv[AES_BLOCK_SIZE];

    // IV sortu
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Gakoaren luzera egokitu
    unsigned char adjusted_key[32]; // AES-256 erabiltzen bada, maximoa 32 byte
    memset(adjusted_key, 0, sizeof(adjusted_key));
    memcpy(adjusted_key, key, key_len < sizeof(adjusted_key) ? key_len : sizeof(adjusted_key));

    // Gakoaren inprimaketa
    AES_set_encrypt_key(adjusted_key, key_len * 8, &enc_key);

    // Enkriptatu
    enc_data_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(enc_data_len);
    if (result.encrypted_data == NULL) {
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Datuak enkriptatu
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &enc_key, iv, AES_ENCRYPT);

    result.encrypted_len = enc_data_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = (unsigned char*)malloc(sizeof(adjusted_key));
    if (result.key != NULL) {
        memcpy(result.key, adjusted_key, sizeof(adjusted_key));
    }

    return result;
}