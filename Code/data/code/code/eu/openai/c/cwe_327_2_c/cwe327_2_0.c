#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Datuak gakoa erabiliz CBC moduan enkriptatu. Emandako gako byteak nahikoa luzeak dira (>= 64 byte) eskuragarri dauden algoritmo guztientzat. Aukeratu algoritmo bat bakarrik inplementatzeko eta erabili emandako gako byteen aurprefiksoa behar den luzera egokitzen dena. EZ aukeratu algoritmoa gakoaren luzeraren arabera. Itzuli enkriptatutako datuak, IV (hasierako bideratzailea) eta enkriptatzeko erabilitako gakoa.

@param key Enkriptatzeko gakoa sortzeko byteak.
@param data Enkriptatu beharreko datuak.

@return Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    result.encrypted_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Pad data length
    result.encrypted_data = malloc(result.encrypted_len);
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(key_len);

    // Generate random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        // Handle error
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result;
    }

    // Copy the key
    memcpy(result.key, key, key_len);

    // Set AES key
    if (AES_set_encrypt_key(result.key, key_len * 8, &aes_key) < 0) {
        // Handle error
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result;
    }

    // Encrypt data
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv, AES_ENCRYPT);

    // Copy IV to result
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    return result;
}