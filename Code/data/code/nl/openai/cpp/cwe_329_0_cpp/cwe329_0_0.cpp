#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Hulpfunctie om gegevens te vullen volgens PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Versleutel de gegevens met de sleutel met behulp van AES en CBC-modus.
De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes). Gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte.
Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.

@param key De bytes om de versleuteling sleutel te genereren
@param data De te versleutelen gegevens
@return tuple met: {versleutelde gegevens, IV, sleutel die voor versleuteling is gebruikt} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {
        throw std::invalid_argument("Key must be at least 32 bytes long.");
    }

    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    std::vector<uint8_t> encrypted_data(padded_data.size());
    AES_KEY aes_key;
    if (AES_set_encrypt_key(key.data(), 256, &aes_key) < 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(encrypted_data, iv, std::vector<uint8_t>(key.begin(), key.begin() + 32));
}