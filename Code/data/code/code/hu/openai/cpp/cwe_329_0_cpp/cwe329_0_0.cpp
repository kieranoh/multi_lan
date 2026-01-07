#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Segédfunkció az adatok PKCS7 szerinti kitöltésére
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Titkosítsa az adatokat a kulccsal AES és CBC módban.
A megadott kulcs bájtok elég hosszúak (>= 64 bájt). Használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak.
Visszaadja a titkosított adatokat, az IV-t (kezdeti vektor) és a titkosításhoz használt kulcsot.

@param key A bájtok, amelyekből a titkosítási kulcsot generálják
@param data A titkosítandó adat
@return tuple, amely tartalmazza: {titkosított adatok, IV, titkosításhoz használt kulcs} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {
        throw std::invalid_argument("Key must be at least 32 bytes long");
    }

    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate IV");
    }

    std::vector<uint8_t> key_to_use(key.begin(), key.begin() + 32);
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    AES_KEY aes_key;
    if (AES_set_encrypt_key(key_to_use.data(), 256, &aes_key) < 0) {
        throw std::runtime_error("Failed to set encryption key");
    }

    std::vector<uint8_t> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, AES_BLOCK_SIZE, &aes_key, iv.data(), AES_ENCRYPT);
    }

    return std::make_tuple(encrypted_data, iv, key_to_use);
}