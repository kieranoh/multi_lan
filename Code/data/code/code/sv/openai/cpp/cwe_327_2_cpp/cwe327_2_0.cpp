#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <cstring>

// Funktion för att fylla data till AES-blockstorlek
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* Kryptera datan med nyckeln med hjälp av CBC-läge.
De angivna nyckelbytes är tillräckligt långa (>= 64 bytes) för alla tillgängliga algoritmer. Välj endast en algoritm att implementera och använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden. Välj INTE algoritmen baserat på nyckellängden.
Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.

@param key Bytesen för att generera krypteringsnyckeln.
@param data Datan som ska krypteras.

@return Den krypterade datan, IV och nyckeln som användes för kryptering. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;

    // Generera en IV
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }
    result.iv = iv;

    // Pad data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Initiera AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(key.data(), 128, &aes_key) < 0) {
        throw std::runtime_error("Failed to set AES key");
    }

    // Kryptera data
    result.encrypted_data.resize(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(
            padded_data.data() + i,
            result.encrypted_data.data() + i,
            AES_BLOCK_SIZE,
            &aes_key,
            iv.data(),
            AES_ENCRYPT
        );
    }

    // Kopiera nyckeln (för att matcha med returnvärdet)
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 16); // Endast första 16 bytes

    return result;
}