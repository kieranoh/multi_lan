#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

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
    // Controleer of de sleutel lang genoeg is (>= 64 bytes)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // AES-256-CBC gebruikt een 256-bit sleutel (32 bytes) en een 128-bit IV (16 bytes)
    const size_t AES_KEY_SIZE = 32; // 256 bits
    const size_t AES_BLOCK_SIZE = 16; // 128 bits
    const size_t IV_SIZE = 16; // 128 bits

    // Haal de eerste AES_KEY_SIZE bytes van de sleutel als versleutelingssleutel
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);

    // Genereer een willekeurige IV
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // Pad de gegevens volgens PKCS7
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // Bereid de uitvoer voor
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // Initialiseer de AES-context
    std::unique_ptr<AES_KEY, decltype(&::AES_set_encrypt_key)> aes_key(new AES_KEY, ::AES_set_encrypt_key);
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, aes_key.get()) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // Voer de versleuteling uit in CBC-modus
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(),
                    aes_key.get(), iv.data(), AES_ENCRYPT);

    return {encrypted_data, iv, encryption_key};
}