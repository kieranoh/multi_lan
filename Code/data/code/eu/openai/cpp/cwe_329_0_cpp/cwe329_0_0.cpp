#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Datuak gakoa erabiliz AES eta CBC moduan enkriptatu. Emandako gako byteak nahikoa luzeak dira (>= 64 byte). Erabili emandako gako byteen aurprefikua behar den luzera egokitzen dena. Itzuli enkriptatutako datuak, IV (hasierako bektorea), eta enkriptatzeko erabilitako gakoa. */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long.");
    }

    // Key and IV initialization
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV.");
    }

    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> cipher_text(padded_data.size());

    AES_KEY aes_key;
    if (AES_set_encrypt_key(key.data(), 512, &aes_key) < 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    // Encrypting data in CBC mode
    AES_cbc_encrypt(padded_data.data(), cipher_text.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(cipher_text, iv, std::vector<uint8_t>(key.begin(), key.begin() + 64));
}