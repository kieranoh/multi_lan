#include <openssl/aes.h>
#include <openssl/rand.h>
#include <tuple>
#include <vector>
#include <stdexcept>

// Pomocná funkce pro vyplnění dat podle PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Zašifrujte data s klíčem pomocí AES a režimu CBC.
Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů). Použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce.
Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.

@param key Bajty pro generování šifrovacího klíče
@param data Data k zašifrování
@return n-tice obsahující: {zašifrovaná data, IV, klíč použitý pro šifrování} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 16) {
        throw std::invalid_argument("Key must be at least 16 bytes long");
    }

    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }

    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data(padded_data.size());

    AES_KEY aes_key;
    if (AES_set_encrypt_key(key.data(), 128, &aes_key) < 0) {
        throw std::runtime_error("Failed to set encryption key");
    }

    // Perform AES CBC encryption
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    std::vector<uint8_t> used_key(key.begin(), key.begin() + 16); // Use first 16 bytes of the key for AES-128

    return std::make_tuple(encrypted_data, iv, used_key);
}